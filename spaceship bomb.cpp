/*
https://www.careercup.com/question?id=5652067409461248
https://www.geeksforgeeks.org/samsung-interview-experience-set-28-campus/

http://ideone.com/JXMl4L
https://ide.geeksforgeeks.org/tiyLThcuSN -> Zero
https://ide.geeksforgeeks.org/3Ks1tpOkwn

*https://code.hackerearth.com/ea07cfD?key=1cb190b158c79639d66d35f7dfa8ef7a -> One

Similr Problem - https://ide.codingblocks.com/s/95965

====================================================================
PROBLEM: Spaceship Maximum Coins (Samsung Coding Test Problem)
====================================================================

You are given a grid consisting of N rows and exactly 5 columns.

Each cell contains one of the following values:

0 → empty cell
1 → coin
2 → enemy

Below the grid there exists a fixed control zone:

        x x S x x

S represents a spaceship and it always starts in the middle column
(column index 2 if 0-indexed).

--------------------------------------------------------------------

GAME MECHANICS

At every second:

• The grid moves DOWN by one row.
  (Equivalent interpretation: the spaceship moves UP one row.)

• During each second the spaceship may:
    1) move left
    2) move right
    3) stay in the same column

--------------------------------------------------------------------

INTERACTION WITH CELLS

If the spaceship enters a cell:

• coin (1)   → collect 1 coin
• enemy (2)  → spaceship crashes and game ends
• empty (0)  → nothing happens

The game also ends when the entire grid has passed.

--------------------------------------------------------------------

SPECIAL ABILITY (BOMB)

The spaceship has EXACTLY ONE bomb.

The bomb can be used at any time (only once).

When used:
All enemies (2) in the 5×5 region immediately ABOVE the spaceship
(i.e., next 5 rows upward) are destroyed and become empty cells (0).

After using the bomb, the spaceship continues the game normally.

--------------------------------------------------------------------

OBJECTIVE

Determine the maximum number of coins that can be collected
before the spaceship crashes or the grid finishes.

--------------------------------------------------------------------

INPUT FORMAT

T
Number of test cases

For each test case:

N
Number of rows in the grid

Next N lines:
Each line contains 5 space-separated integers (0, 1, or 2)

--------------------------------------------------------------------

OUTPUT FORMAT

For each test case print:

#case_number : maximum_coins

--------------------------------------------------------------------

SAMPLE INPUT
--------------------------------------------------------------------
1
6
0 1 0 2 0
0 2 2 2 1
0 2 1 1 1
1 0 1 0 0
0 0 1 2 2
1 1 0 0 1

--------------------------------------------------------------------

SAMPLE OUTPUT
--------------------------------------------------------------------
#1 : 5

--------------------------------------------------------------------

EXPLANATION

Initial Position:
Spaceship starts at bottom center column.

STEP 1:
Move LEFT → collect coin → coins = 1

STEP 2:
Move RIGHT → collect coin → coins = 2

STEP 3:
Stay in same column → collect 2 more coins → coins = 4

At this point enemies block all possible paths.
If we continue without bomb → spaceship crashes.

So we use the bomb.

The bomb destroys all enemies in the next 5 rows above the spaceship.

After clearing enemies:
We can safely move once more and collect one additional coin.

Final coins collected = 5

--------------------------------------------------------------------

OBSERVATION

This problem is NOT a shortest path problem.

This is a RECURSION / BACKTRACKING simulation problem:

At every step you must consider:
    - 3 movement choices
    - whether to use the bomb now or later

You must explore all valid possibilities and choose the path
that yields the maximum number of coins.

====================================================================
*/

MY CODE 
#include <iostream>
#include <vector>

using namespace std;

void updateMatrix(int row,vector<vector<int>>& grid){
    if(row < 0){
        return;
    }
    for(int i = row;i >= max(0,row - 4);i--){
        for(int j = 0;j < 5;j++){
            if(grid[i][j] == 2){
                grid[i][j] = 0;
            }
        }
    }
}

int findMaxCoins(int i,int j,int bomb,vector<vector<int>>& grid){

    if(j >= 5 || j < 0){
        return 0;
    }
    if(i <= 0){
        return 0;
    }
    int best = 0;
    bool safeMove = false;
    for(int k = -1;k <= 1;k++){
        int nj = j + k;

        if(nj >= 5 || nj < 0){
            continue;
        }
        if(grid[i - 1][nj] != 2){
            safeMove = true;
            int coin = (grid[i-1][nj] == 1 ? 1 : 0);
            best = max(best,findMaxCoins(i-1,nj,bomb,grid) + coin);
        }
    }

    if(!safeMove && bomb > 0){
        vector<vector<int>> temp = grid;
        updateMatrix(i-1, grid);
        best = findMaxCoins(i, j, 0, grid);
        grid = temp;
    }

    return best;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input.txt","r",stdin);

    freopen("output.txt","w",stdout);

    int row;
    cin >> row;
    vector<vector<int>> grid(row,vector<int>(5));
    for(int i = 0;i<row;i++){
        for(int j = 0;j < 5;j++){
            cin >> grid[i][j];
        }
    }
    int maxi = findMaxCoins(row,2,1,grid);
    cout << maxi;
    return 0;
}

/*

#include<bits/stdc++.h>
using namespace std;
void updateMatrix(int row,char ** matrix){
    if(row<0){
        return;
    }
    int upLimit=max(0,row-4);
    for(int i=row;i>=upLimit;i--){
        for(int j=0;j<=4;j++){
            if(matrix[i][j]=='2'){
                matrix[i][j]='0';
            }
        }
    }
}
int findMaxPoints(int row,int col,int bombs,char ** matrix){
    if(row<=0 || col<0 || col>=5){
        return 0;
    }
    int answer=0;
    if(row>0 && matrix[row-1][col]!='2'){
        answer=max(answer,(matrix[row-1][col]=='1'?1:0)+findMaxPoints(row-1,col,bombs,matrix));
    }
    if(col>0 && row>0 && matrix[row-1][col-1]!='2'){
        answer=max(answer,(matrix[row-1][col-1]=='1'?1:0)+findMaxPoints(row-1,col-1,bombs,matrix));
    }
    if(col<4 && row>0 && matrix[row-1][col+1]!='2'){
        answer=max(answer,(matrix[row-1][col+1]=='1'?1:0)+findMaxPoints(row-1,col+1,bombs,matrix));
    }

    if(answer==0 && bombs>0){
        updateMatrix(row-1,matrix);
        answer=findMaxPoints(row,col,bombs-1,matrix);
    }

    return answer;
}
int main(){
    int t, row;
    cin >> t;
    int tNo = 0;
    while(t--){
        cin >> row;
        char ** matrix=new char*[row + 2];
        for(int i=0; i<row; i++){
            matrix[i]=new char[5];
            for(int j=0;j<5;j++){
                cin>>matrix[i][j];
            }
        }
        tNo++;
        cout<< "#" << tNo << " : " << findMaxPoints(row,2,1,matrix) << endl;        
    }
    return 0;
}

/* 
No rech top 

#include <iostream>
using namespace std;
int det[5][5];
int mat[13][5];

void detonate(int r)
{
    for(int i=r;i>r-5 && i>=0;i--)
    {
        for(int j=0;j<5;j++)
        {
            det[r-i][j]=0;
            if(mat[i][j]==2)
            {
                det[r-i][j]=2;
                mat[i][j]=0;
            }
        }
    }
}

void undet(int r)
{
    for(int i=r;i>r-5 && i>=0;i--)
        for(int j=0;j<5;j++)
        {
            if( det[r-i][j]==2)
                mat[i][j]=2;
        }
}
void func(int n,int pos,int c,int &max)
{
    if(pos>4||pos<0||c<0)
        return;

    if(mat[n][pos]==2)
        c-=1;
    else if(mat[n][pos]==1)
        c+=1;

    if(n==0)
    {
        if(c>max)
            max=c;
        return;
    }
    else
    {
        func(n-1,pos+1,c,max);
        func(n-1,pos-1,c,max);
        func(n-1,pos,c,max);
    }
}
int main()
{
    int t;
    cin>>t;
    int count=1;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=0;i<n;i++)
            for(int j=0;j<5;j++)
                cin>>mat[i][j];
        int max=-1,c;
        for(int j=0;j<5;j++)
            mat[n][j]=0;
        mat[n][2]=3;
        for(int j=n;j>=5;j--)
        {
            c=-1;
            detonate(j-1);
            func(n,2,0,c);
            if(c>max)
                max=c;
            undet(j-1);
        }
        if(max<0)
            max=-1;
        cout<<"#"<<count<<" "<<max<<endl;
        count++;
    }
}
*/

/*
#include <iostream>
using namespace std;
int det[5][5];
int mat[13][5];

void detonate(int r){
    for(int i=r;i>r-5 && i>=0;i--){
        for(int j=0;j<5;j++){
            det[r-i][j]=0;
            if(mat[i][j]==2){
                det[r-i][j]=2;
                mat[i][j]=0;
            }
        }
    }
}

void undet(int r){
    for(int i=r;i>r-5 && i>=0;i--)
        for(int j=0;j<5;j++){
            if( det[r-i][j]==2)
                mat[i][j]=2;
        }
}

void func(int n,int pos,int c,int &max){
    if(pos>4||pos<0||c<0)
        return;

    if(mat[n][pos]==2)
        c-=1;
    else if(mat[n][pos]==1)
        c+=1;

    if(n==0){
        if(c>max)
            max=c;
        return;
    }
    else{
        func(n-1,pos+1,c,max);
        func(n-1,pos-1,c,max);
        func(n-1,pos,c,max);
    }
}

int main(){
    int t;
    cin>>t;
    int count=1;
    while(t--){
        int n;
        cin>>n;

        for(int i=0;i<n;i++)
            for(int j=0;j<5;j++)
                cin>>mat[i][j];
        for(int j=0;j<5;j++)
            mat[n][j]=0;
        mat[n][2]=3;

        int max=-1,c;
        for(int j=n;j>=5;j--){
            c=-1;
            detonate(j-1);
            func(n,2,0,c);

            if(c>max)
                max=c;
            
            undet(j-1);
        }

        if(max<0)
            max=-1;
        
        cout<<"#"<<count<<" "<<max<<endl;
        count++;
    }
}
*/
