# /*

# PROBLEM: Mr. Lee – Minimum Airfare (Samsung SWC Coding Test)

Mr. Lee works at a company headquarters (Office 0).
He must travel to multiple international branch offices to help them.

However, flight tickets are expensive.

He wants to:

1. Start from his company (city 0)
2. Visit every other office EXACTLY ONCE
3. Finally return back to his company (city 0)
4. Spend the MINIMUM possible airfare

You are given the airfare between every pair of cities.

---

INPUT DESCRIPTION

T → number of test cases

For each test case:

N → number of offices (cities) including headquarters
(1 ≤ N ≤ 12)

Then an N × N matrix is given:

matrix[i][j] = airfare to travel from city i to city j

Rules:
• matrix[i][i] = 0
• If matrix[i][j] = 0 (i ≠ j) → travel is NOT possible
• City 0 is the headquarters (start and end point)

---

OUTPUT

For each test case print:

Minimum airfare required to:
start at city 0 → visit all cities exactly once → return to city 0

If no complete tour exists, print -1.

---

## SAMPLE INPUT

3

5
0 14 4 10 20
14 0 7 8 7
4 5 0 7 16
11 7 9 0 2
18 7 17 4 0

5
9 9 2 9 5
6 3 5 1 5
1 8 3 3 3
6 0 9 6 8
6 6 9 4 8

3
0 2 24
3 0 2
0 4 0

---

## SAMPLE OUTPUT

30
18
31

---

EXPLANATION (Test Case 1)

Start at city 0.

We must visit cities {1,2,3,4} exactly once and return to 0.

One optimal route:

0 → 2 → 1 → 3 → 4 → 0

Cost:
0→2 = 4
2→1 = 5
1→3 = 8
3→4 = 2
4→0 = 11

Total = 4 + 5 + 8 + 2 + 11 = 30

No other permutation gives a smaller cost.

---

IMPORTANT OBSERVATION

This is the classic:

TRAVELLING SALESMAN PROBLEM (TSP)

Constraints N ≤ 12 mean:
DP bitmask is possible,
but Samsung typically expects
DFS + Backtracking + Pruning.

State:
(current_city, visited_set, current_cost)

Key idea:
Try all permutations but prune paths
when cost already exceeds best answer.

===============================================================
*/

#include<iostream>
#include<climits>
using namespace std;

int N, result;

void minCostMrLee(int **arr, bool *visited, int count, int cost, int src){
    // Base Case
    if(count == N-1){
    	/* Corner Case if no path exists from last city */
        if(arr[src][0] != 0)
        	result = min(result, cost + arr[src][0]);
        return;
    }
    
    // Main Case
    for(int i=0; i<N; i++){
        if(!visited[i] && arr[src][i] != 0){
            visited[i] = true;
            minCostMrLee(arr, visited, count + 1, cost + arr[src][i], i);
            visited[i] = false;
        }
    }
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> N;
		int **arr = new int*[N];
		for(int i=0; i<N; i++){
			arr[i] = new int[N];
		}
        bool *visited = new bool[N];
		
        for(int i=0; i<N; i++){
            visited[i] = false;
			for(int j=0; j<N; j++){
				cin >> arr[i][j];
			}
		}
		
        result = INT_MAX;    
        
        visited[0] = true;
        
        minCostMrLee(arr, visited, 0, 0, 0);
        result != INT_MAX ? cout << result << "\n" : cout << "-1\n";
	}
	return 0;
}

/*
#include<iostream>
using namespace std;
int arr[1000][1000];
bool visited[1000];
int ans = 1000000;
void dfs(int n,int count,int cost,int last)
{
    //cout<<last<<" ";
    if(count==n)
    {
        //cout<<endl;
        int cost1 = cost + arr[last][0];
        if(cost1<ans)
            ans = cost1;
    }
    for(int i=1;i<n;i++)
    {
        if(visited[i])
            continue;
        if(arr[last][i]==0)
            continue;
        visited[i]=true;
        int cost1 = cost + arr[last][i];
        dfs(n,count+1,cost1,i);
        visited[i]=false;
    }
    return;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        ans = 1000000;
        cin>>n;
        for(int i=0;i<n;i++)
            visited[i]=false;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
           {
               cin>>arr[i][j];
           }
        }
        dfs(n,1,0,0);
        cout<<ans<<endl;
    }
}
*/
