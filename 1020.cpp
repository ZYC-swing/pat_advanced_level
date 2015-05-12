//1020. Tree Traversals
/*
Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
Sample Output:
4 1 6 3 5 7 2
*/
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 30
int postorder[MAXN],inorder[MAXN];

typedef struct node{
	int num;
	node *left;
	node *right;
}BiNode;

BiNode *bulidTree(int postLeft, int postRight, int inLeft, int inRight){
	BiNode *father;
	int leftNum,rightNum;
	
	father = (BiNode *)malloc(sizeof(BiNode));
	father->num = postorder[postRight];
	for(int i=inLeft; i<=inRight; i++){
		if(inorder[i]==postorder[postRight]){
			leftNum = i-inLeft;
			rightNum = inRight-i;
			break;
		}
	}

	if(leftNum){
		father->left = bulidTree(postLeft, postLeft+leftNum-1, inLeft, inLeft+leftNum-1);
	}
	else{
		father->left = NULL;
	}
	if(rightNum){
		father->right = bulidTree(postRight-rightNum, postRight-1, inRight-rightNum+1, inRight);
	}
	else{
		father->right = NULL;
	}

	return father;
}

int main(int argc, char const *argv[])
{
	int n;
	BiNode *head;
	queue<BiNode*> result;

	cin >> n;
	for(int i=0; i<n; i++){
		cin >> postorder[i];
	}
	for(int i=0; i<n; i++){
		cin >> inorder[i];
	}

	head = bulidTree(0,n-1,0,n-1);
	result.push(head);
	bool first = true;
	while(!result.empty()){
		if(first){
			first = false;
		}
		else{
			cout << " ";
		}
		BiNode *tmp = result.front();
		cout << tmp->num;
		if(tmp->left!=NULL){
			result.push(tmp->left);
		}
		if(tmp->right!=NULL){
			result.push(tmp->right);
		}
		result.pop();
	}

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> postOrder, inOrder;

struct BiTree{
	int val;
	BiTree *left;
	BiTree *right;
	BiTree(int n) :val(n), left(nullptr), right(nullptr){}
};

BiTree *build(int postLeft, int postRight, int inLeft){
	if (postLeft > postRight){
		return nullptr;
	}
	BiTree *root = new BiTree(postOrder[postRight]);
	int left;
	for (left = 0; inOrder[left] != postOrder[postRight]; ++left);
	int leftNum = left - inLeft;
	root->left = build(postLeft, postLeft + leftNum - 1, inLeft);
	root->right = build(postLeft + leftNum, postRight - 1, left + 1);
	return root;
}

int main(){
	int n;
	cin >> n;
	postOrder.resize(n);
	inOrder.resize(n);
	for (int i = 0; i < n; ++i){
		cin >> postOrder[i];
	}
	for (int i = 0; i < n; ++i){
		cin >> inOrder[i];
	}
	BiTree *root = build(0, n - 1, 0);
	bool first = 1;
	queue<BiTree*> qq;
	qq.push(root);
	while (!qq.empty()){
		BiTree *tmp = qq.front();
		qq.pop();
		if (first){
			first = 0;
		}
		else{
			cout << " ";
		}
		cout << tmp->val;
		if (tmp->left != nullptr){
			qq.push(tmp->left);
		}
		if (tmp->right != nullptr){
			qq.push(tmp->right);
		}
	}
	system("pause");
	return 0;
}