//1064. Complete Binary Search Tree
/*
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=1000). Then N distinct non-negative integer keys are given in the next line. All the numbers in a line are separated by a space and are no greater than 2000.

Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input:
10
1 2 3 4 5 6 7 8 9 0
Sample Output:
6 3 8 1 5 7 9 0 2 4
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

vector<int> numbers;

typedef struct node{
	int value;
	node *left;
	node *right;
}BiNode;

void nodeCnt(int n, int *leftCnt, int *rightCnt){
	int h;

	h = (int)(log(n*1.0)/log(2.0))+1;
	if(h==1){
		*leftCnt = *rightCnt = 0;
	}
	else{
		if(3*pow(2.0,h-2)-1>=n){
			*rightCnt = pow(2.0,h-2)-1;
			*leftCnt = n-1-*rightCnt;
		}
		else{
			*leftCnt = pow(2.0,h-1)-1;
			*rightCnt = n-1-*leftCnt;
		}
	}
}

BiNode *buildTree(int leftIndex, int rightIndex){
	int n,leftCnt,rightCnt;
	BiNode *father;

	n = rightIndex-leftIndex+1;
	father = (BiNode*)malloc(sizeof(BiNode));
	nodeCnt(n,&leftCnt,&rightCnt);
	father->value = numbers[leftIndex+leftCnt];
	if(leftCnt==0){
		father->left = NULL;
	}
	else{
		father->left = buildTree(leftIndex,leftIndex+leftCnt-1);
	}
	if(rightCnt==0){
		father->right = NULL;
	}
	else{
		father->right = buildTree(rightIndex-rightCnt+1,rightIndex);
	}
	return father;
}

int main(int argc, char const *argv[])
{
	int n;

	cin >> n;
	numbers.resize(n);
	for(int i=0; i<n; i++){
		cin >> numbers[i];
	}
	sort(numbers.begin(),numbers.end());

	BiNode *head = buildTree(0,n-1);

	bool first = true;
	queue<BiNode*> qq;
	qq.push(head);
	while(!qq.empty()){
		if(first){
			first = false;
		}
		else{
			cout << " ";
		}
		cout << qq.front()->value;
		if(qq.front()->left!=NULL){
			qq.push(qq.front()->left);
		}
		if(qq.front()->right!=NULL){
			qq.push(qq.front()->right);
		}
		qq.pop();
	}

	system("pause");
	return 0;
}