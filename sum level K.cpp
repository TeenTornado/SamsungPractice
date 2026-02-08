/*
------------------------------------------------------------
PROBLEM: Sum of Nodes at a Given Level in a Serialized Binary Tree
------------------------------------------------------------

A binary tree is represented as a string using bracket notation.

Each node is encoded as:

    (value left_subtree right_subtree)

Where:
- value : integer value of the node (can be negative)
- left_subtree : representation of the left child
- right_subtree : representation of the right child
- empty subtree is written as ()

Root node is at LEVEL 0.

Your task:
Given a level X and the tree string S, print the sum of all node
values present at level X.

IMPORTANT:
You should NOT construct the actual tree. The problem can be solved
by parsing the string and tracking the current depth using brackets.

------------------------------------------------------------
INPUT FORMAT
------------------------------------------------------------
Line 1 : Integer X (required level)
Line 2 : String S (serialized tree)

------------------------------------------------------------
OUTPUT FORMAT
------------------------------------------------------------
Print a single integer → sum of nodes at level X.

------------------------------------------------------------
EXAMPLE 1
Input:
1
(1(2()())(3()()))

Output:
5

Explanation:
Tree:
      1
     / \
    2   3

Nodes at level 1 → 2 + 3 = 5

------------------------------------------------------------
EXAMPLE 2
Input:
3
(0(5(6()())(-4()(9()())))(7(1()())(3()())))

Output:
6

Nodes at level 3 → 6, -4, 1, 3
Sum = 6

------------------------------------------------------------
IDEA ( HINT )
------------------------------------------------------------
'('  → go one level deeper
')'  → return to parent level

The nesting depth of parentheses = node depth.

When a number finishes parsing, we are currently standing
at that node's level. If level == X, add it to sum.

Time Complexity: O(N)
Space Complexity: O(1)
------------------------------------------------------------
*/



#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

#define scll(x) scanf("%lld",&x);
#define sci(x) scanf("%d",&x);
#define prll(x) printf("%lld\n",x);
#define pri(x) printf("%d\n",x);

/*
3 
(0(5(6()())(-4()(9()())))(7(1()())(3()())))
*/

int main()
{
	int arr[2][100]={0};	
	int size = 0;
	int x;
	string str;
	
	cin>>x;
	cin>>str;
	int level=0, temp=0, commit=0, neg=0;
	for(int i=0; i<str.length(); i++){
		
		if(str[i]=='(' || str[i]==')'){
			if(commit == 1){
				if(neg==1){
					temp=temp*-1;
					neg=0;
				}
				
				arr[0][size]=level;
				arr[1][size]=temp;
				size++;
				temp=0;		
			}
			
			if(str[i]=='('){			
				level++;
			}
			else if(str[i]==')'){
				level--;
			}
			commit=0;
		}
		else if(str[i]=='-'){
			neg=1;
			commit = 1;
		}
		else{
			temp= temp*10 + str[i] - '0';
			commit = 1;
		}	
			
	}

	int temp0,temp1;
	for(int i=0;i<size-1;i++){
		for(int j=i+1; j<size; j++){
			if(arr[0][j] > arr[0][i]){
				temp0=arr[0][j];
				temp1=arr[1][j];
				arr[0][j]=arr[0][i];
				arr[1][j]=arr[1][i];
				arr[0][i]=temp0;
				arr[1][i]=temp1;
			}
			
		}
	}
	
	int sum = 0;
	for(int i=0;i<size;i++){
		if(arr[0][i]==x+1)	sum+=arr[1][i];
	}
	
	cout<<sum<<endl;
	return 0;
}
