/* 
https://www.careercup.com/question?id=5745468609921024 
https://gist.github.com/gunpreet34/d0e45eedd61dadbf42fe6540da98facf
https://ideone.com/SlO2P5 - BitMasking Solution
http://ideone.com/tdNRtQ - TARGET_SAMSUNG
*/
# /*

# PROBLEM: Mr. Kim’s Refrigerator Delivery Route

Mr. Kim must deliver refrigerators to N customers.

He starts from his OFFICE, must visit EVERY customer exactly once,
and finally return to his HOME.

Each location (office, home, and customers) is given as a coordinate
(x, y) on a 2D grid.

The travel distance between two locations (x1, y1) and (x2, y2) is:

```
|x1 - x2| + |y1 - y2|
```

(This is Manhattan Distance.)

Your task is to determine the MINIMUM total distance Mr. Kim must
travel if he chooses the optimal visiting order of customers.

Important:
• Every customer must be visited exactly once.
• You can visit customers in ANY order.
• You must start at the office.
• You must end at Mr. Kim’s home.

---

INPUT FORMAT

T → number of test cases

For each test case:

Line 1:
N  → number of customers (5 ≤ N ≤ 10)

Line 2:
Coordinates given in sequence:

OfficeX OfficeY HomeX HomeY
Customer1X Customer1Y
Customer2X Customer2Y
...
CustomerNX CustomerNY

---

OUTPUT FORMAT

For each test case print:

#testcase_number minimum_distance

---

## EXAMPLE INPUT

1
5
0 0 100 100 70 40 30 10 10 5 90 70 50 20

---

## EXAMPLE OUTPUT

#1 200

---

EXPLANATION

Start: Office (0,0)
End:   Home (100,100)

Customers:
(70,40), (30,10), (10,5), (90,70), (50,20)

Mr. Kim may visit customers in any order.

One optimal visiting sequence:

Office → Customer3 → Customer2 → Customer5 → Customer1 → Customer4 → Home

Compute the Manhattan distances between consecutive locations.
The minimum possible total distance = 200.

---

OBSERVATION

This is NOT a shortest path graph problem.

This is a permutation search problem.

We must try all possible visiting orders of customers and
choose the order with minimum travel distance.

This is equivalent to a SMALL-SIZED Travelling Salesman Problem (TSP):

start node fixed (office)
end node fixed (home)
visit all intermediate nodes exactly once

Since N ≤ 10, a backtracking DFS solution is feasible.

====================================================================
*/

MY CODE

#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

int N;
int ans;

// office and home
int officeX, officeY;
int homeX, homeY;

// customers
int customerX[11], customerY[11];

bool visited[11];

// Manhattan distance
int dist(int x1,int y1,int x2,int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

// DFS permutation search
void dfs(int currX,int currY,int count,int totalDist){

    // pruning
    if(totalDist >= ans)
        return;

    // all customers visited → go home
    if(count == N){
        totalDist += dist(currX,currY,homeX,homeY);
        ans = min(ans,totalDist);
        return;
    }

    // try next customer
    for(int i=0;i<N;i++){
        if(!visited[i]){

            visited[i] = true;

            dfs(customerX[i],customerY[i],
                count+1,
                totalDist + dist(currX,currY,customerX[i],customerY[i]));

            visited[i] = false; // backtrack
        }
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    cin >> N;

    // office then home
    cin >> officeX >> officeY >> homeX >> homeY;

    for(int i = 0; i < N; i++){
        cin >> customerX[i] >> customerY[i];
        visited[i] = false;
    }

    ans = INT_MAX;

    // start from office
    dfs(officeX,officeY,0,0);

    cout << ans;
    return 0;
}

/*

#include<iostream>
#include<climits>
using namespace std;
int x[20],y[20],n,ans;

int abs(int i){//Absolute function
	if(i>0){
		return i;
	}
	return -i;
}

int dist(int i, int j){//Calc dist between 2 points
    int x1 = x[i], x2 = x[j];
    int y1 = y[i], y2 = y[j];
    
    return (abs(x1-x2) + abs(y1-y2));
}

void optimalPath(int x,bool visited[],int nodes,int value){
	if(n == nodes){//If number of nodes equal n then set value of answer
		ans = min(ans,value + dist(x,n+1));
	}
	for(int i=1;i<=n;i++){
		if(!visited[i]){
			visited[i] = true;
			optimalPath(i,visited,nodes+1,value + dist(x,i));//Dfs call
			visited[i] = false;
		}
	}
}

int main(){
	int tCases;
	cin >> tCases;//For testcases
	for(int i=0;i<tCases;i++){
		ans=INT_MAX;//Set ans to max value
		cin >> n;
		cin >> x[n+1] >> y[n+1] >> x[0] >> y[0];//Input destination and source x,y coordinates
		for(int i=1;i<=n;i++){//Input drop off location coordinates
			cin >> x[i] >> y[i];
		}
		bool visited[n+2]={false};
		optimalPath(0,visited,0,0);
		cout << "#" << i+1 << " " << ans << endl;
	}
	return 0;
}

/*
#include <iostream>
#include <cstring>
using namespace std;

bool marked[105][105];

struct point {
    int x;
    int y;
};

int absDiff(point i, point j)
{
    int xd = (i.x > j.x) ? i.x - j.x : j.x - i.x ;
    int yd = (i.y > j.y) ? i.y - j.y : j.y - i.y ;
    return xd + yd ;
}

int solve(point a, point b, point arr[], point &end, int nodes)
{
    int curDist = absDiff(a, b);
    marked[b.x][b.y] = 1;
    int dist = 0, minDist = 1000007 ;
    for(int i = 0; i < nodes; i++){
        if(marked[arr[i].x][arr[i].y] == 0){
            dist = solve(b, arr[i], arr, end, nodes);
            if(dist < minDist)
                minDist = dist ;
        }
    }
    marked[b.x][b.y] = 0;
    if(minDist == 1000007){
        minDist = absDiff(b, end);
    }
    
    return curDist + minDist ;
}

int main()
{
    int test;
    cin >> test ;
    for(int l = 1; l <= test; l++){
        
        int nodes;
        cin >> nodes ;
        point start, end;
        point arr[nodes + 3];
        
        cin >> start.x >> start.y ;
        cin >> end.x >> end.y ;
        
        for(int u = 0; u < nodes; u++){
            cin >> arr[u].x >> arr[u].y ;
        }
        
        int dist = 0, minDist = 100007 ;
        for(int i = 0; i < nodes; i++){
            memset(marked, 0, sizeof(bool) * (nodes + 2) * (nodes + 2));
            dist = solve(start, arr[i], arr, end, nodes);
            if(dist < minDist)
                minDist = dist ;
        }
        
        cout << "#" << l << " " << minDist << endl ;
    }
    return 0;
}
*/
