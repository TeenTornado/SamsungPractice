**Problem: Sum of Nodes at a Given Level in a Serialized Binary Tree**

---

### Problem Statement

You are given a binary tree encoded as a string using bracket notation.
Each node of the tree is represented in the following format:

```
(value left_subtree right_subtree)
```

* `value` → integer value of the node (can be negative)
* `left_subtree` → representation of the left child
* `right_subtree` → representation of the right child
* An empty subtree is represented as `()`

Your task is to compute the **sum of all node values present at a given level `X`**.

The root node is considered to be at **level 0**.

---

### Input Format

1. The first line contains an integer `X` — the required level.
2. The second line contains a string `S` — the serialized representation of the binary tree.

---

### Output Format

Print a single integer — the sum of all nodes present at level `X`.

---

### Constraints

* `0 ≤ X ≤ 10^5`
* `1 ≤ |S| ≤ 10^5`
* Node values range from `-10^9` to `10^9`
* The tree is always valid and properly balanced in parentheses.

---

### Example 1

**Input**

```
2
(1(2()())(3()()))
```

**Explanation**

The tree:

```
      1
     / \
    2   3
```

Nodes at level 2 → none

Output:

```
0
```

---

### Example 2

**Input**

```
1
(1(2()())(3()()))
```

Nodes at level 1 → `2` and `3`

Output:

```
5
```

---

### Example 3

**Input**

```
3
(0(5(6()())(-4()(9()())))(7(1()())(3()())))
```

Nodes at level 3 → `6, -4, 1, 3`

Output:

```
6
```

---

### Important Observations

* Every `'('` means moving **down one level** in the tree.
* Every `')'` means returning **up one level**.
* The nesting depth of parentheses directly corresponds to the depth of a node.

---

### Expected Approach

The problem should be solved in **O(N)** time using a single pass over the string.
Constructing an explicit tree is **not required** and may lead to unnecessary memory usage.

---

### Tags

`Tree` `DFS` `Stack` `Parsing` `Simulation` `String Processing`


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
