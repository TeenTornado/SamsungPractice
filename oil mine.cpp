/*
https://www.careercup.com/question?id=5740719907012608
https://stackoverflow.com/questions/39673898/divide-array-into-k-contiguos-partitions-such-that-sum-of-maximum-partition-is-m/39675396
http://ideone.com/r60yH4 - Sameer Code
https://www.careercup.com/question?id=5730470801702912
*/

/*
====================================================================
PROBLEM: Fair Distribution of Oil Mines (Samsung Coding Test)
====================================================================

An island contains a circular chain of oil mines.

There are M oil mines arranged in a circle.
Each mine produces a certain amount of oil.

There are N companies that must be assigned these mines.

RULES OF DISTRIBUTION
--------------------------------------------------------------------
1) Each company must receive a CONTIGUOUS block of mines.

2) Since the mines are circular, the first and last mines are also
   considered adjacent.

   Example:
   mines = [6, 13, 10, 2]

   Valid partitions:
   [6,13] [10,2]
   [2,6] [13,10]   (because circle)

3) Every mine must be assigned to exactly one company.

4) No company can take mines from the middle of another company’s block.

--------------------------------------------------------------------

FAIRNESS CRITERIA
--------------------------------------------------------------------
After distributing the mines:

Each company will have a total oil value (sum of its mines).

Let:
MAX = company with highest oil
MIN = company with lowest oil

We define unfairness = MAX − MIN

Your task is to distribute the mines such that this unfairness
is MINIMIZED.

--------------------------------------------------------------------

INPUT FORMAT
--------------------------------------------------------------------
T  → number of test cases

For each test case:

N M
N = number of companies
M = number of oil mines

Next line:
M integers representing oil in each mine (circular order)

--------------------------------------------------------------------

OUTPUT FORMAT
--------------------------------------------------------------------
For each test case print:
minimum possible unfairness.

--------------------------------------------------------------------

SAMPLE INPUT
--------------------------------------------------------------------
2
2 4
6 13 10 2
2 4
6 10 13 2

--------------------------------------------------------------------

SAMPLE OUTPUT
--------------------------------------------------------------------
5
1

--------------------------------------------------------------------

EXPLANATION
--------------------------------------------------------------------

Test Case 1:
Companies = 2
Mines = [6, 13, 10, 2]

Possible circular partitions:

Partition 1:
[6,13] and [10,2]
sums = 19 and 12
difference = 7

Partition 2:
[13,10] and [2,6]
sums = 23 and 8
difference = 15

Partition 3:
[10,2,6] and [13]
sums = 18 and 13
difference = 5  <-- MINIMUM

Answer = 5


Test Case 2:
Companies = 2
Mines = [6, 10, 13, 2]

Best partition:
[6,10] and [13,2]
sums = 16 and 15
difference = 1  <-- MINIMUM

Answer = 1

--------------------------------------------------------------------

IMPORTANT OBSERVATION
--------------------------------------------------------------------
This is NOT a greedy problem.

This is a:
    Backtracking / Recursion / Partitioning problem.

We must try every possible contiguous circular partition
and track the minimum difference.

Key challenge:
Handling circular array + contiguous segments simultaneously.

Time Complexity:
Exponential (but constraints are small in Samsung tests)

====================================================================
*/

#include <iostream>
#include <climits>
using namespace std;

int companies, mines, ANS;

int MIN(int x, int y){
    return (x>=y) ? y : x;
}

int MAX(int x, int y){
    return (x>=y) ? x : y;
}

void calculateOilMines(int i, int *oilMines, bool *visited, int minV, int maxV, int sum,
                        int nodes, int &ANS){
    // Base Case
    if(visited[i]){
        int newMin = MIN(sum, minV);
        int newMax = MAX(sum, maxV);

        if(nodes == companies - 1){
            ANS = min(ANS, newMax - newMin);
        }
        return;
    }

    // Main Case
    visited[i] = 1;
    int j = (i + 1) % mines;

    calculateOilMines(j, oilMines, visited, minV, maxV, sum + oilMines[i], nodes, ANS);

    int newMin = MIN(sum, minV);
    int newMax = MAX(sum, maxV);

    calculateOilMines(j, oilMines, visited, newMin, newMax, oilMines[i], nodes + 1, ANS);

    visited[i] = 0;
    return;
}

int main() {
	// your code goes here
	int t;
	cin >> t;
	while(t--){
		cin >> companies >> mines;
		int  *oilMines = new int[mines + 1];
		bool *visited  = new bool[mines + 1];

		for(int i=0; i<mines; i++){
            cin >> oilMines[i];
            visited[i] = 0;
        }
			
        ANS = INT_MAX;    
        for(int i=0; i<mines; i++)
            calculateOilMines(i, oilMines, visited, INT_MAX, INT_MIN, 0, 0, ANS);  

		cout << ANS <<endl;		
	}
	return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
int ans=9999;
void findMinDiff(int company[],int n)
{
    int mini = 9999;
    int maxi=0;
    for(int i=0;i<n;i++)
    {
        mini = min(mini,company[i]);
        maxi = max(maxi,company[i]);
    }
    if(ans>(maxi-mini))
        ans = maxi-mini;
}
void findAns(int end,int curr,int oil[],int company[],int m,int n,int num)
{
    if((curr+1)%m==end)
    {
        for(int j = num;j<n;j++)
        {
            company[j]+=oil[curr];
            findMinDiff(company,n);
            company[j]-=oil[curr];
        }
        return;
    }
    if(num==n)
        return;
    company[num]+=oil[curr];
    findAns(end,(curr+1)%m,oil,company,m,n,num);
    company[num]-=oil[curr];
    findAns(end,curr,oil,company,m,n,num+1);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ans=9999;
        int n,m;
        cin>>n>>m;
        int oil[m];
        for(int i=0;i<m;i++)
            cin>>oil[i];
        int company[n];
        for(int i=0;i<n;i++)
        {
            company[i]=0;
        }
        for(int i=0;i<m;i++)
        {
            findAns(i,i,oil,company,m,n,0);
        }
        cout<<ans<<endl;
    }
}
*/
