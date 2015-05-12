//1043. Is It a Binary Search Tree 
/*
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
If we swap the left and right subtrees of every node, then the resulting tree is called the Mirror Image of a BST.

Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence of a BST or the mirror image of a BST.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=1000). Then N integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in a line "YES" if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, or "NO" if not. Then if the answer is "YES", print in the next line the postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
7
8 6 5 7 10 8 11
Sample Output 1:
YES
5 7 6 8 11 10 8
Sample Input 2:
7
8 10 11 8 6 7 5
Sample Output 2:
YES
11 8 10 7 5 6 8
Sample Input 3:
7
8 6 8 5 10 9 11
Sample Output 3:
NO
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct node{
	int num;
	node *left;
	node *right;
}BiNode;

vector<int> preOrder;
vector<int> inOrder;
int cnt;//计数，保证输出根节点后不输出多余空格

bool isSame(int preLeft, int preRight, int inLeft, int inRight){
	vector<int> nodes[2];
	for(int index=preLeft; index<=preRight; index++){
		nodes[0].push_back(preOrder[index]);
	}
	for(int index=inLeft; index<=inRight; index++){
		nodes[1].push_back(inOrder[index]);
	}
	sort(nodes[0].begin(),nodes[0].end());
	sort(nodes[1].begin(),nodes[1].end());
	if(nodes[0].size()!=nodes[1].size()){
		return 0;
	}
	else{
		int i = 0;
		while(i<nodes[0].size()){
			if(nodes[0][i]!=nodes[1][i]){
				return false;
			}
			i++;
		}
		return true;
	}
}

BiNode *buildTree(int preLeft, int preRight, int inLeft, int inRight, bool mirror){
	if(!isSame(preLeft,preRight,inLeft,inRight)){
		return NULL;
	}
	else{
		BiNode *father = (BiNode *)malloc(sizeof(BiNode));
		father->num = preOrder[preLeft];
		int i;
		for(i=inLeft; i<=inRight; i++){
			if(inOrder[i]==preOrder[preLeft]){
				break;
			}
		}
		//如果是镜像，那么所有和父节点值相同的应该放在左子树
		if(mirror){
			while(i<inRight && inOrder[i+1]==preOrder[preLeft]){
				i++;
			}
		}
		int leftNum,rightNum;
		leftNum = i-inLeft;
		rightNum = inRight-i;
		if(leftNum==0){
			father->left = NULL;
		}
		else{
			father->left = buildTree(preLeft+1, preLeft+leftNum, inLeft, inLeft+leftNum-1, mirror);
			//左子树建立失败
			if(father->left==NULL){
				return NULL;
			}
		}
		if(rightNum==0){
			father->right = NULL;
		}
		else{
			father->right = buildTree(preRight-rightNum+1, preRight, inRight-rightNum+1, inRight, mirror);
			//右子树建立失败
			if(father->right==NULL){
				return NULL;
			}
		}
		return father;
	}
}

void postTraversal(BiNode *father){
	if(father==NULL){
		return;
	}
	else{
		postTraversal(father->left);
		postTraversal(father->right);
		cout << father->num;
		if(--cnt){
			cout << " ";
		}
	}
}

int main(int argc, char const *argv[])
{
	int n;

	cin >> n;
	for(int i=0; i<n; i++){
		int num;
		cin >> num;
		preOrder.push_back(num);
	}
	inOrder = preOrder;
	sort(inOrder.begin(),inOrder.end());

	BiNode *head;
	head = buildTree(0,n-1,0,n-1,0);

	bool flag = true;
	if(head==NULL){
		reverse(inOrder.begin(),inOrder.end());
		head = buildTree(0,n-1,0,n-1,1);
		if(head==NULL){
			flag = false;
		}
	}
	if(flag){
		cout << "YES" << endl;
		//后序遍历
		cnt = n;
		postTraversal(head);
	}
	else{
		cout << "NO";
	}

	system("pause");
	return 0;
}