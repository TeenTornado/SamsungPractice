PROBLEM: Detect Cycle in an Undirected Graph

You are given an undirected graph consisting of V vertices numbered
from 0 to V-1 and E edges.

Each edge connects two vertices u and v, and the connection is bidirectional.

Your task is to determine whether the graph contains a cycle.

--------------------------------------------------

DEFINITION

A cycle exists in an undirected graph if you can start from a vertex
and come back to the same vertex by following a path of distinct edges,
without reusing an edge and without using the trivial parent connection.

In simple words:
If during traversal you reach a visited node that is NOT the parent,
then a cycle exists.

--------------------------------------------------

INPUT FORMAT

First line contains an integer V — number of vertices.

Second line contains an integer E — number of edges.

Next E lines each contain two integers:
u v

Meaning there is an undirected edge between u and v.

--------------------------------------------------

OUTPUT FORMAT

Print:

"Cycle Present"

if the graph contains a cycle

OR

"Cycle Not Present"

if the graph does not contain a cycle.

--------------------------------------------------

EXAMPLE INPUT
5
5
0 1
1 2
2 3
3 4
4 1

EXAMPLE OUTPUT
Cycle Present

--------------------------------------------------

EXPLANATION

The edge (4,1) connects back to a previously visited node that is not
the parent, forming a loop:

1 → 2 → 3 → 4 → 1

Hence a cycle exists.

--------------------------------------------------
MY CODE 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
    bool findCycle(int i,vector<int>& vis,vector<vector<int>>& adj){
        vis[i] = 1;
        queue<pair<int,int>> q;
        q.push({i,-1});
        
        while(!q.empty()){
            int node = q.front().first;
            int prev = q.front().second;
            q.pop();
            
            for(auto itr : adj[node]){
                if(!vis[itr]){
                    q.push({itr,node});
                    vis[itr] = 1;
                }else if(prev != itr){
                    return true;
                }
            }
        }
        return false;
    }
    bool isCycle(int V, vector<vector<int>>& edges) {

        vector<vector<int>> adj(V);
        vector<int> vis(V,0);
        for(auto edge : edges){
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        bool cycle = false;
        for(int i = 0;i<V;i++){
            if(!vis[i]){
                 cycle = findCycle(i,vis,adj);
                 if(cycle == true){
                     return cycle;
                 }
            }
        }
        return cycle;
    }

int main(){
    int V;
    cin >> V;
    int n;
    cin >> n;
    vector<vector<int>> edges(n,vector<int>(n));
    for(int i = 0;i<n;i++){
        int u,v;
        cin >> u >> v;
        edges.push_back({u,v});
    }
    bool cycle = isCycle(V,edges);
    if(cycle){
        cout << "Cycle Present";
    }else{
        cout << "Cycle Not Present";
    }
}    

    
#include <iostream>
using namespace std;

int a[100][100], n;

bool findcycle(int st, bool visited[], int parent, int &prev){
    visited[st]=true;
    
    for(int j=0;j<n;j++){

        if(a[st][j] == 1 && visited[j] == false){

            if( findcycle(j, visited, st, prev) ){
                if(st==prev){
                    cout << st << " ";
                    prev = -1;
                }
                else if(prev != -1){
                    cout << st << " ";
                }

                return true;
            }

        }
        else if(a[st][j] == 1 && parent != j && visited[j] == true){
            cout << st << " ";    
            prev = j;
            return true;
        }

    }
    return false;
}

int main(){
    memset(a,0,sizeof(a));
    int m;
    cin >> n >> m;
    
    int x,y;
    while(m--){
        cin>>x>>y;
        a[x][y]=1;
        a[y][x]=1;
    }
    
    bool visited[n] = {false};
    int parent = -1, prev = -1;
    findcycle(0,visited,parent,prev);
    
    return 0;
}
