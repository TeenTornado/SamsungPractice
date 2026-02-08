# /*

# PROBLEM: Jewel Maze — Maximum Jewels Without Reusing a Passage

You are given a maze of size N × N.

Each cell of the maze can be:
0 → empty passage (you can walk)
1 → wall (blocked)
2 → jewel (can be collected once)

You start at the ENTRANCE located at the top-left cell (0,0).
You must reach the EXIT located at the bottom-right cell (N-1,N-1).

Your goal is to collect the MAXIMUM number of jewels while travelling
from entrance to exit.

IMPORTANT RULE:
You are NOT allowed to use the same passage twice.
In other words, you cannot visit any cell more than once in a single path.

You may move in 4 directions:
UP, DOWN, LEFT, RIGHT

A wall cell (1) cannot be entered.

If multiple paths exist, choose the path that collects the maximum jewels.

After finding the optimal path:
• Mark every cell used in the final path with value 3
• Other cells remain unchanged
• Also print the number of jewels collected

---

INPUT FORMAT

T → number of test cases

For each test case:

N → size of maze (1 ≤ N ≤ 10)

Next N lines:
N integers per line representing the maze.

---

OUTPUT FORMAT

For each test case:

Print the maze with the chosen path marked using 3.
Then print the total number of jewels collected.

---

## SAMPLE INPUT

1
4
0 0 2 0
1 0 1 0
0 2 0 0
0 0 0 2

---

EXPLANATION

You must start at (0,0) and reach (3,3).

You may choose different routes, but:
• you cannot revisit a cell
• you cannot pass through walls
• you want to collect maximum jewels

Among all valid paths, choose the one collecting the most jewels.

Finally mark that path using 3 and print the jewel count.

---

OBSERVATION / INTENDED SOLUTION

This is NOT a shortest path problem.

This is a:
BACKTRACKING / DFS + STATE TRACKING problem.

Why BFS fails:
BFS finds shortest path.
But shortest path ≠ maximum jewels.

We must explore ALL possible paths from start to exit,
while keeping track of:

* visited cells
* jewels collected

Whenever we reach the exit:
update the best answer if jewel count is larger.

Time complexity is manageable because:
N ≤ 10  → grid size ≤ 100 cells.

====================================================================
*/

MY CODE 

#include <iostream>
#include <vector>

using namespace std;
int bestJewels = 0;
int N;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};


void dfs(int x,int y,vector<vector<int>>& cave,
         vector<vector<int>>& vis,int jewels){
        
    if(x == 0 && y == 0){
        bestJewels = max(bestJewels, jewels);
        return;
    }

    for(int k=0;k<4;k++){
        int nx = x + dx[k];
        int ny = y + dy[k];

        if(nx<0 || ny<0 || nx>=N || ny>=N)
            continue;

        if(vis[nx][ny])
            continue;

        if(cave[nx][ny] == 1)
            continue;

        vis[nx][ny] = 1;

        if(cave[nx][ny] == 2)
            dfs(nx,ny,cave,vis,jewels+1);
        else
            dfs(nx,ny,cave,vis,jewels);

        vis[nx][ny] = 0;
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("input.txt","r",stdin);

    freopen("output.txt","w",stdout);

    cin >> N;
    vector<vector<int>> cave(N,vector<int>(N));
    vector<vector<int>> vis(N,vector<int>(N,0));
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            cin >> cave[i][j];
        }
    }
    vis[N-1][N-1] = 1;
    if(cave[N-1][N-1] == 2){
        dfs(N-1,N-1,cave,vis,1);
    }
    else{
        dfs(N-1,N-1,cave,vis,0);
    }

    cout<<bestJewels;

    return 0;
}

/*

#include<iostream>
#include<climits>
#define MAX 21
using namespace std;

int n, ans;

bool isValid(int i, int j){
	return (i>=0 && i<n && j>=0 && j<n);
}

void printMatrix(int **arr){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << arr[i][j] << " ";	
		cout << endl;
	}
}

int dirX[] = {1,0,-1,0};
int dirY[] = {0,1,0,-1};

void jewelMaze(int **maze, int x, int y, int value, int **visited, int **path){
	if(x == n-1 && y == n-1){
		if(value >= ans){
			ans = value;
			
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++)
				    if(visited[i][j]){
				    	path[i][j] = 3;
					}
					else{
						path[i][j] = maze[i][j];
					}	
			}
		}
		return;
	}

	for(int i=0; i<4; i++){
		int newX = x + dirX[i];
		int newY = y + dirY[i];
		
		if(isValid(newX, newY)){
			
			if(visited[newX][newY] == 0 && maze[newX][newY] == 0){
				visited[newX][newY] = 1;
				jewelMaze(maze, newX, newY, value, visited, path);
				visited[newX][newY] = 0;
			}
			
			if(visited[newX][newY] == 0 && maze[newX][newY] == 2){
				visited[newX][newY] = 1;
				jewelMaze(maze, newX, newY, value+1, visited, path);
				visited[newX][newY] = 0;
			}

		}
	}
	
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int **maze = new int * [n + 1];
		for(int i=0; i<n; i++){
			maze[i] = new int[n + 1];
		}
		
		int **visited = new int * [n + 1];
		for(int i=0; i<n; i++){
			visited[i] = new int[n + 1];
		}
		
		int **path = new int * [n + 1];
		for(int i=0; i<n; i++){
			path[i] = new int[n + 1];
		}

		// Cleaner and input Maze
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> maze[i][j];
				visited[i][j] = 0;
				path[i][j] = 0;
			}
		}
		
		ans = INT_MIN;
		
		int sX = 0, sY = 0;
		visited[sX][sY] = 1;
		
		// printMatrix(maze);
		
		if(maze[sX][sY] == 2)
			jewelMaze(maze, sX, sY, 1, visited, path);
		else
			jewelMaze(maze, sX, sY, 0, visited, path);
			
			
		cout << "Jewel collected : " << ans << endl;
		
		cout << "Path traversed --> " << endl;
		printMatrix(path); 
		
		cout << endl;
	}
	return 0;
}

*/
