PROBLEM: Maximum Score Path in a Grid

You are given an N × N grid representing a game board.

Each cell of the grid contains either:
• A digit '0' to '9' representing the points collected when you step on that cell
• The character 'x' representing a blocked cell that cannot be visited

You start at the top-left cell (0,0) and must reach the bottom-right cell (N-1,N-1).

NOTE:
The starting cell and the destination cell DO NOT contribute any points.

--------------------------------------------------

ALLOWED MOVES
From a cell (i, j) you may move:

1. Right        → (i, j+1)
2. Down         → (i+1, j)
3. Diagonal     → (i+1, j+1)

You are not allowed to step on blocked cells ('x').

--------------------------------------------------

TASK
For each test case, determine:

1) The maximum points that can be collected along any valid path
2) The number of distinct paths that achieve this maximum score

If no valid path exists from start to destination, print:
0 0

--------------------------------------------------

INPUT FORMAT
The first line contains an integer T — number of test cases.

For each test case:
• First line contains an integer N — size of the grid
• Next N lines each contain N characters separated by space
  (each character is a digit '0'–'9' or 'x')

--------------------------------------------------

OUTPUT FORMAT
For each test case, output:
<maximum_score> <number_of_paths>

--------------------------------------------------

SAMPLE INPUT
1
3
0 1 1
1 x 1
1 1 0

SAMPLE OUTPUT
3 2

--------------------------------------------------

EXPLANATION

Possible valid paths from (0,0) to (2,2):

Path 1:
(0,0) → (0,1) → (0,2) → (1,2) → (2,2)
Points collected = 1 + 1 + 1 = 3

Path 2:
(0,0) → (1,0) → (2,1) → (2,2)
Points collected = 1 + 1 + 1 = 3

Both paths produce the maximum possible score (3).

Therefore:
Maximum Score = 3
Number of Maximum Score Paths = 2


--------------------------------------------------

// MY CODE 
#include <iostream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
pair<int,int> totalMaxPath(int i,int j,vector<vector<pair<int,int>>>& dp,vector<vector<char>>& grid){
    int n = grid.size();
    if(i < 0 || j < 0 || j >= n || i >= n || grid[i][j] == 'x'){
        return {-1e9,0};
    }
    if(i == 0 && j == 0){
        return {0,1};
    }
    if(dp[i][j].first != -1){
        return dp[i][j];
    }
    int val = grid[i][j] - '0';
    pair<int,int> up = totalMaxPath(i - 1,j,dp,grid) ;
    pair<int,int> left = totalMaxPath(i ,j - 1,dp,grid) ;
    pair<int,int> ldiag = totalMaxPath(i - 1,j - 1,dp,grid);
    int best = max(up.first,max(left.first,ldiag.first));
    if(best == -1e9){
        return dp[i][j] = {-1e9,0};
    }
    int ways = 0;
    if(up.first == best){
        ways += up.second;
    }
    if(left.first == best){
        ways += left.second;
    }
    if(ldiag.first == best){
        ways += ldiag.second;
    }
    return dp[i][j] = {best + val, ways};
}

int main(){
    int n;
    cin >> n;
    vector<vector<char>> grid(n,vector<char>(n));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cin >> grid[i][j];
        }
    }
    vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(n,{-1,-1}));

    pair<int,int> ans = totalMaxPath(n-1,n-1,dp,grid);

    if(ans.first < 0){
        cout <<"0 0";
    }else{
        cout << ans.first << " " << ans.second;
    }
    return 0;
}


#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        bool isNoPath = false;
        cin>>n;
        char arr[n][n];
        pair<int,int> dp[n][n];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>arr[i][j];
                dp[i][j].first = 0;
                dp[i][j].second = 0;
            }
        }
        arr[0][0]='0';
        arr[n-1][n-1]='0';
        
        //Move to last coulumn
        for(int i=n-2;i>=0;i--)
        {
            if(arr[i][n-1]=='x')
            {
                for(int j=i;j>=0;j--)
                {
                    dp[j][n-1].first = dp[j][n-1].second = INT_MIN;
                }
                break;
            }
            else
            {
                dp[i][n-1].first = dp[i+1][n-1].first+(arr[i][n-1]-48);
                dp[i][n-1].second = 1;
            }
        }    
        //Move to last row
        for(int i=n-2;i>=0;i--)
        {
            if(arr[n-1][i]=='x')
            {
                for(int j=i;j>=0;j--)
                {
                    dp[n-1][j].first = dp[n-1][j].second = INT_MIN;
                }
                break;
            }
            else
            {
                dp[n-1][i].first = dp[n-1][i+1].first+(arr[n-1][i]-48);
                dp[n-1][i].second = 1;
            }
        }
        
        //Move to Remaining matrix
        for(int i=n-2;i>=0;i--)
        {
            for(int j=n-2;j>=0;j--)
            {
                if(arr[i][j]=='x')
                {
                    dp[i][j].first = dp[i][j].second = INT_MIN;
                }
                else
                {
                    int maxi = max(dp[i][j+1].first,max(dp[i+1][j+1].first,dp[i+1][j].first));
                    int path = 0;
                    if(dp[i][j+1].first==maxi)
                        path += dp[i][j+1].second;
                    if(dp[i+1][j+1].first==maxi)
                        path += dp[i+1][j+1].second;
                    if(dp[i+1][j].first==maxi)
                        path += dp[i+1][j].second;
                    if(maxi==INT_MIN)
                    {
                        isNoPath = true;
                        break;
                    }
                    dp[i][j].first = maxi+(arr[i][j]-48);
                    dp[i][j].second = path;
                }
            }
        }
        if(isNoPath)
            cout<<"0"<<" "<<"0"<<endl;
        else
        cout<<dp[0][0].first<<" "<<dp[0][0].second<<endl;   
    }
	return 0;
}
