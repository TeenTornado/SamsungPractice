/*
https://www.hackerearth.com/problem/algorithm/question-7-4

/*
====================================================================
PROBLEM: Underground Tunnel Escape (Samsung R&D Coding Test)
====================================================================

A fugitive is trapped inside an underground sewer system.

The sewer system is represented as a grid of size N × M.
Each cell contains a pipe structure which determines the
directions in which movement is possible.

Each cell value represents a pipe type:

0 → No pipe (blocked cell)

1 → Can move in all 4 directions (Up, Down, Left, Right)
2 → Vertical pipe (Up, Down)
3 → Horizontal pipe (Left, Right)
4 → Up and Right
5 → Down and Right
6 → Down and Left
7 → Up and Left

The fugitive starts at a given manhole position (R, C).

He can move through connected pipes only if:

1) The current pipe has an opening toward the neighbor.
2) The neighboring pipe has an opening back toward the current cell.

For example:
You can move UP only if:
- current cell allows UP
AND
- the upper cell allows DOWN.

--------------------------------------------------------------------

TIME LIMIT CONDITION

The fugitive can move only for L units of time.

• Each move to an adjacent connected pipe takes 1 unit of time.
• The starting position counts as time = 1.

Your task is to determine how many distinct cells the fugitive
can reach within L time units.

--------------------------------------------------------------------

INPUT FORMAT

T  → number of test cases

For each test case:

N M R C L
N = number of rows
M = number of columns
R = starting row (0-indexed)
C = starting column (0-indexed)
L = maximum time allowed

Next N lines:
Each line contains M integers representing pipe types (0–7)

--------------------------------------------------------------------

OUTPUT FORMAT

For each test case print:
the number of reachable cells.

--------------------------------------------------------------------

SAMPLE INPUT
--------------------------------------------------------------------
1
5 6 2 1 3
0 0 5 3 6 0
0 0 2 0 2 0
3 3 1 3 7 0
0 0 2 0 0 0
0 0 4 6 5 0

--------------------------------------------------------------------

SAMPLE OUTPUT
--------------------------------------------------------------------
6

--------------------------------------------------------------------

EXPLANATION

Starting position = (2,1)

Time = 1
We are at starting pipe → reachable cells = 1

Time = 2
We can move to adjacent connected pipes based on openings.

Time = 3
We expand further through valid pipe connections.

After exploring all valid connected pipes within 3 time units,
the fugitive can reach a total of 6 distinct cells.

--------------------------------------------------------------------

IMPORTANT OBSERVATION

This is NOT a shortest path problem.

This is a BFS level traversal problem:

• Each BFS level = 1 time unit
• Stop BFS when distance > L
• Count number of visited cells

Key logic:
You can move between two cells only if BOTH pipes connect to each other.

Example:
Moving RIGHT:
current.right == true AND neighbor.left == true

====================================================================
*/

#include<iostream>
using namespace std;

struct Node{
    bool left, right, up, down;
};

struct Point{
    int x, y;  
};

int n, m, sX, sY, len;
int arr[1005][1005];
int vis[1005][1005], dis[1005][1005];

int result;
Node pipes[1005][1005];
Point queue[1000005];

bool isValid(int i, int j){
    return (i>=0 && i<n && j>=0 && j<m);
}

void bfs(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vis[i][j] = 0;
            dis[i][j] = 0;
        }
    }
    
    int front = 0, rear = 0; 
    
    dis[sX][sY] = 1;
    vis[sX][sY] = 1;
    
    if( arr[sX][sY] == 0 ){
        result = 0;
        return;
    }
    
    queue[rear].x = sX;
    queue[rear].y = sY;
    rear = (rear + 1) % 1000005;
    
    while(front != rear){
        int p = queue[front].x;
        int q = queue[front].y;
        front = (front + 1) % 1000005;
        
        if( 1 + dis[p][q] <= len ){
            
            /* Row Up */
            if( isValid(p-1, q) && vis[p-1][q] == 0 && pipes[p-1][q].down && pipes[p][q].up ){
                vis[p-1][q] = 1;
                dis[p-1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p-1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Row Down */
            if( isValid(p+1, q) && vis[p+1][q] == 0 && pipes[p+1][q].up && pipes[p][q].down ){
                vis[p+1][q] = 1;
                dis[p+1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p+1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Column Left */
            if( isValid(p, q-1) && vis[p][q-1] == 0 && pipes[p][q-1].right && pipes[p][q].left ){
                vis[p][q-1] = 1;
                dis[p][q-1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q-1;
                rear = (rear + 1) % 1000005;
            }          

            /* Column Right */
            if( isValid(p, q+1) && vis[p][q+1] == 0 && pipes[p][q+1].left && pipes[p][q].right ){
                vis[p][q+1] = 1;
                dis[p][q+1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q+1;
                rear = (rear + 1) % 1000005;
            }          
                        
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	//code
	int t;
	cin >> t;
	while(t--){
	    result = 1;
	    cin >> n >> m >> sX >> sY >> len;
	    
	    for(int i=0; i<n; i++){
	        for(int j=0; j<m; j++){
	            cin >> arr[i][j];
	            
	            if( arr[i][j] == 1 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            } 
	            else if( arr[i][j] == 2 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 3 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	            else if( arr[i][j] == 4 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;
	            }
	            else if( arr[i][j] == 5 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 6 ){
	                pipes[i][j].left = true;
                    pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 7 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;	                
	            }
	            else{
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	 
	        }
	    }
	    
	    bfs();
	    cout << result << "\n";
	}
	return 0;
}
