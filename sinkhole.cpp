# /*

# PROBLEM: Largest Square Plot With At Most One Sinkhole

You are given a rectangular land plot of size N × M.

Some cells in the plot contain sinkholes (damaged land).
You want to build a square-shaped facility on this land.

However, construction rules allow:
The chosen square region may contain AT MOST ONE sinkhole.

Your task is to find the LARGEST POSSIBLE square that can be built
under this condition.

If multiple squares have the same maximum size:
• Prefer the square having fewer sinkholes.
• If still tied, output any one of them.

The grid coordinates start from (1,1) at the bottom-left corner.

For the chosen square, output:
Bottom-left coordinate (xb, yb)
Top-right coordinate  (xt, yt)

---

INPUT FORMAT

T → number of test cases

For each test case:

N M
N = number of rows
M = number of columns

K → number of sinkholes

Next K lines:
x y  → coordinates of sinkholes (1-indexed)

---

OUTPUT FORMAT

For each test case print:

#i xb yb xt yt

where:
i  = test case number
xb,yb = bottom-left coordinate of the square
xt,yt = top-right coordinate of the square

---

CONSTRAINTS

1 ≤ N, M ≤ 1000
1 ≤ K ≤ N + M
Time Limit: 1 second

---

WHAT YOU NEED TO FIND

Among all possible square subgrids in the matrix,
find the largest side-length square containing
no more than ONE sinkhole.

---

EXAMPLE

Input:
1
5 5
2
2 2
4 4

Explanation:

A 5×5 grid is given.
Sinkholes exist at:
(2,2) and (4,4)

We must find the biggest square subgrid that contains
at most one sinkhole.

If a 4×4 square contains both sinkholes → invalid.
If a 3×3 square contains only one sinkhole → valid.

We search all possible squares and choose the largest valid one.

---

OBSERVATION / INTENDED SOLUTION

Brute force checking every square is too slow:
O(N^3)

Instead:

1. Build a 2D Prefix Sum matrix
   → Quickly count number of sinkholes inside any sub-square in O(1)

2. Binary search the side length of the square.

3. For each candidate side length:
   Check if ANY square of that size has ≤ 1 sinkhole.

Time Complexity:
O(N × M × log(min(N,M)))

====================================================================
*/

#include <iostream>
using namespace std;

#define INT_MAX 100000;

int xb,yb,xt,yt;

int fun(int dp[][1001], int N, int M, int k){
	int msum = INT_MAX;
	for(int i=0; i<=N-k; i++){
		for(int j=0; j<=M-k; j++){
			int sum = dp[i+k][j+k]-dp[i+k][j]-dp[i][j+k]+dp[i][j];
			if(sum < msum){
				msum = sum;
				if(msum <=1){
					xb = i+k;
					yb = j+1;
					xt = i+1;
					yt = j+k;
				}
			}
		}
	}
	return msum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	/* input */
	int N,M;
	cin>>N>>M;
	int A[N][M];
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			A[i][j]=0;
		}
	}
	int K;
	cin>>K;
	for(int i=0; i<K; i++){
		int x,y;
		cin>>x>>y;
		A[x-1][y-1]=1;
	}
	
	int dp[1001][1001]; /* dp[i][j] = sum of submatrix top-left(0,0) to bottom-right(i,j) */
	for(int i=0; i<1001; i++){
		for(int j=0; j<1001; j++){
			dp[i][j]=0;
		}
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+A[i-1][j-1];
		}
	}
	/* applying binary search */
	int l=1, r=min(M,N);
	int ones;
	while(l<r){
		int mid = (l+r)/2;
		ones = fun(dp,N,M,mid);
		//if no. of ones > 1 means we need to decrease the submatix size 
		if(ones >1){
			r = mid;
		}
		//else increase the submatrix size
		else{
			l = mid+1;
		}
	}
	/* output */
	cout<<xb<<" "<<yb<<" "<<xt<<" "<<yt<<endl;
	return 0;
}
