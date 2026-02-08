/*
------------------------------------------------------------
PROBLEM: Spread Time in a Grid (BFS Flood Fill)
------------------------------------------------------------

You are given a 2D grid of size M x N.

Each cell contains either:
0 → blocked cell (cannot be entered)
1 → open cell (can be visited)

From a given starting position (r, c), a signal spreads to its
adjacent cells every 1 unit of time.

The signal can move only in 4 directions:
up, down, left, right.

From the starting cell, the signal spreads simultaneously to all
reachable neighbouring open cells, and then continues spreading
from those cells in subsequent time units.

Your task is to determine how many time units are required for the
signal to reach all cells that are reachable from the starting cell.

------------------------------------------------------------
INPUT FORMAT
------------------------------------------------------------
T                → number of test cases

For each test case:
M N              → number of rows and columns
Next M lines:    → grid values (0 or 1)
r c              → starting position (1-indexed)

------------------------------------------------------------
OUTPUT FORMAT
------------------------------------------------------------
For each test case print:

Case #k
X

Where X is the number of time units required for the spread to
finish.

------------------------------------------------------------
SAMPLE INPUT
------------------------------------------------------------
1
4 5
1 1 0 1 1
1 1 1 0 1
0 1 1 1 1
0 0 1 1 1
2 2

------------------------------------------------------------
SAMPLE OUTPUT
------------------------------------------------------------
Case #1
5

------------------------------------------------------------
EXPLANATION
------------------------------------------------------------

Grid (r=2, c=2 is the starting cell):

Row 1: 1 1 0 1 1
Row 2: 1 1 1 0 1   ← start at (2,2)
Row 3: 0 1 1 1 1
Row 4: 0 0 1 1 1

Time = 0
Start at (2,2)

Time = 1
We can move to all adjacent open cells:
(2,1), (2,3), (1,2), (3,2)

Time = 2
From those, we reach:
(1,1), (3,3)

Time = 3
Then:
(3,4), (4,3)

Time = 4
Then:
(3,5), (4,4)

Time = 5
Finally:
(2,5), (4,5), (1,5)

The farthest reachable cell from the start is reached after 5 steps.

Therefore, the answer = 5.

------------------------------------------------------------
OBSERVATION
------------------------------------------------------------
This problem is equivalent to performing Breadth First Search (BFS)
from the starting cell and finding the maximum distance to any
reachable open cell.

The BFS "level" represents time.
------------------------------------------------------------
*/

MY CODE 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int bfs(int srow,int scol,vector<vector<int>>& grid){
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int,pair<int,int>>> q;
    q.push({0,{srow,scol}});
    grid[srow][scol] = 0;
    int drRow[] = {-1,1,0,0};
    int drCol[] = {0,0,-1,1};
    int maxTime = 0;
    while(!q.empty()){
        int time = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();
        maxTime = max(time,maxTime);
        for(int k = 0;k < 4;k++){
            int nrow = row + drRow[k];
            int ncol = col + drCol[k];

            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m 
            && grid[nrow][ncol] != 0){
                q.push({time + 1,{nrow,ncol}});
                grid[nrow][ncol] = 0;
            }
        }
    }
    return maxTime;
}
int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> grid(n,vector<int>(m));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin >> grid[i][j];
        }
    }
    int srow,scol; // Start Row , Start Col
    cin >> srow >> scol;
    int time = bfs(srow,scol,grid);
    cout << time;
    return 0;
}

//https://www.cnblogs.com/kingshow123/p/practicec1.html
#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;
typedef struct
{
    int x;
    int y;
    int level;
}data;
int mv[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
//int mv[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};

int main()
{
    //freopen("test.txt","r",stdin);
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        int n,m;
        int r,c;
        cin>>n>>m;
        int a[m+1][n+1];
        memset(a,0,sizeof(int)*m*n);
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                cin>>a[i][j];
            }
        }

        cin>>r>>c;
        data d,d1,d2;
        queue<data> qt;
        int tmx,tmy,tml;
        d.x = c;
        d.y = r;
        d.level = 1;
        qt.push(d);
        a[d.x][d.y] = 2;
        while(!qt.empty())
        {
            d1 = qt.front();
            qt.pop();
            for(int k=0; k<4; k++)
            {
                tmx = d1.x + mv[k][0];
                tmy = d1.y + mv[k][1];
                tml = d1.level + 1;
                if(a[tmx][tmy] == 1)
                {
                    d2.x = tmx;
                    d2.y = tmy;
                    d2.level = tml;
                    a[d2.x][d2.y] = 2;
                    qt.push(d2);
                }
            }
        }
        cout<<"Case #"<<t<<endl;
        cout<<tml-1<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}
