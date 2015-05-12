//1066. Root of AVL Tree
/*
An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.

    
    
Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=20) which is the total number of keys to be inserted. Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print ythe root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88
*/

// 先写了个非递归插入节点的版本。。。写了三个多小时（= =的确是有点手生，忒慢了），虽然一次AC了，但真是又臭又长。。。
// #include <iostream>
// #include <algorithm>
// using namespace std;

// typedef struct node{
// 	int value;
// 	int lheight;
// 	int rheight;
// 	node *left;
// 	node *right;
// 	node *father;
// }BiNode;

// BiNode *adjust(BiNode *father){
// 	if(father->lheight-father->rheight>1){
// 		//LL
// 		if(father->left->lheight>father->left->rheight){
// 			BiNode *tmp = father->left;
// 			tmp->father = father->father;
// 			if(tmp->right!=NULL){
// 				tmp->right->father = father;
// 			}
// 			father->father = tmp;
// 			father->left = tmp->right;
// 			tmp->right = father;
// 			if(father)
// 			father = tmp;
// 			//更新左右树高
// 			if(father->right->left==NULL){
// 				father->right->lheight = 0;
// 			}
// 			else{
// 				father->right->lheight = max(father->right->left->lheight,father->right->left->rheight)+1;
// 			}
// 			father->rheight = max(father->right->lheight,father->right->rheight)+1;
// 		}
// 		//LR
// 		else{
// 			BiNode *tmp = father->left;
// 			tmp->father = tmp->right;
// 			tmp->right->father = father;
// 			if(tmp->right->left!=NULL){
// 				tmp->right->left->father = tmp;
// 			}
// 			father->left = tmp->right;
// 			tmp->right = tmp->right->left;
// 			father->left->left = tmp;

// 			tmp = father->left;
// 			tmp->father = father->father;
// 			if(tmp->right!=NULL){
// 				tmp->right->father = father;
// 			}
// 			father->father = tmp;
// 			father->left = tmp->right;
// 			tmp->right = father;
// 			father = tmp;
// 			//更新左右树高
// 			if(father->left->right==NULL){
// 				father->left->rheight = 0;
// 			}
// 			else{
// 				father->left->rheight = max(father->left->right->lheight,father->left->right->rheight)+1;
// 			}
// 			if(father->right->left==NULL){
// 				father->right->lheight = 0;
// 			}
// 			else{
// 				father->right->lheight = max(father->right->left->lheight,father->right->left->rheight)+1;
// 			}
// 			father->lheight = max(father->left->lheight,father->left->rheight)+1;
// 			father->rheight = max(father->right->lheight,father->right->rheight)+1;
// 		}
// 	}
// 	else{
// 		//RL
// 		if(father->right->lheight>father->right->rheight){
// 			BiNode *tmp = father->right;
// 			tmp->father = tmp->left;
// 			tmp->left->father = father;
// 			if(tmp->left->right!=NULL){
// 				tmp->left->right->father = tmp;
// 			}
// 			father->right  = tmp->left;
// 			tmp->left = tmp->left->right;
// 			father->right->right = tmp;

// 			tmp = father->right;
// 			tmp->father = father->father;
// 			if(tmp->left!=NULL){
// 				tmp->left->father = father;
// 			}
// 			father->father = tmp;
// 			father->right = tmp->left;
// 			tmp->left = father;
// 			father = tmp;
// 			//更新左右树高
// 			if(father->right->left==NULL){
// 				father->right->lheight = 0;
// 			}
// 			else{
// 				father->right->lheight = max(father->right->left->lheight,father->right->left->rheight)+1;
// 			}
// 			if(father->left->right==NULL){
// 				father->left->rheight = 0;
// 			}
// 			else{
// 				father->left->rheight = max(father->left->right->lheight,father->left->right->rheight)+1;
// 			}
// 			father->lheight = max(father->left->lheight,father->left->rheight)+1;
// 			father->rheight = max(father->right->lheight,father->right->rheight)+1;
// 		}
// 		//RR
// 		else{
// 			BiNode *tmp = father->right;
// 			tmp->father = father->father;
// 			if(tmp->left!=NULL){
// 				tmp->left->father = father;
// 			}
// 			father->father = tmp;
// 			father->right = tmp->left;
// 			tmp->left = father;
// 			father = tmp;
// 			//更新左右树高
// 			if(father->left->right==NULL){
// 				father->left->rheight = 0;
// 			}
// 			else{
// 				father->left->rheight = max(father->left->right->lheight,father->left->right->rheight)+1;
// 			}
// 			father->lheight = max(father->left->lheight,father->left->rheight)+1;
// 		}
// 	}

// 	return father;
// }

// BiNode *insertNode(BiNode *root, int number){
// 	BiNode *tmp = root;
// 	BiNode *father = NULL;

// 	bool left;
// 	while(tmp!=NULL){
// 		father = tmp;
// 		if(tmp->value>number){
// 			tmp = tmp->left;
// 			left = true;
// 		}
// 		else{
// 			tmp = tmp->right;
// 			left = false;
// 		}
// 	}

// 	tmp = (BiNode*)malloc(sizeof(BiNode));
// 	tmp->value = number;
// 	tmp->lheight = 0;
// 	tmp->rheight = 0;
// 	tmp->left = tmp->right = NULL;
// 	tmp->father = father;

// 	if(father!=NULL){
// 		if(left){
// 			father->left = tmp;
// 		}
// 		else{
// 			father->right = tmp;
// 		}
// 	}

// 	while(father!=NULL){
// 		if(father->left==tmp){
// 			if(father->lheight==max(tmp->lheight,tmp->rheight)+1){
// 				return root;
// 			}
// 			else{
// 				father->lheight = max(tmp->lheight,tmp->rheight)+1;
// 			}
// 		}
// 		else{
// 			if(father->rheight==max(tmp->lheight,tmp->rheight)+1){
// 				return root;
// 			}
// 			else{
// 				father->rheight = max(tmp->lheight,tmp->rheight)+1;
// 			}
// 		}
// 		if(abs(father->lheight-father->rheight)>1){
// 			break;
// 		}
// 		tmp = father;
// 		father = father->father;
// 	}
	
// 	if(father==NULL){
// 		return tmp;
// 	}

// 	BiNode *pre = father->father;
// 	left = true;
// 	if(pre!=NULL && pre->right==father){
// 		left = false;
// 	}
// 	father = adjust(father);
// 	if(pre!=NULL){
// 		if(left){
// 			pre->left = father;
// 		}
// 		else{
// 			pre->right = father;
// 		}
// 	}

// 	root = father;
// 	while(root->father!=NULL){
// 		root = root->father;
// 	}

// 	return root;
// }

// int main(int argc, char const *argv[])
// {
// 	BiNode *head = NULL;
// 	int n;

// 	cin >> n;
// 	while(n--){
// 		int num;
// 		cin >> num;
// 		head = insertNode(head, num);
// 	}

// 	cout << head->value;

// 	system("pause");
// 	return 0;
// }

#include <iostream>
#include <algorithm>
using namespace std;

typedef struct node{
	int value;
	node *left;
	node *right;
	node(int v):value(v),left(NULL),right(NULL){};
	node():left(NULL),right(NULL){};
}BiNode;

int getHeight(BiNode *T){
	if(T==NULL){
		return 0;
	}
	return max(getHeight(T->left),getHeight(T->right))+1;
}

bool isBalanced(BiNode *T){
	int lHeight,rHeight;

	lHeight = getHeight(T->left);
	rHeight = getHeight(T->right);
	
	return abs(lHeight-rHeight)<=1;
}

BiNode *LL(BiNode *a){
	BiNode *b;

	b = a->left;
	a->left = b->right;
	b->right = a;

	return b;
}

BiNode *RR(BiNode *a){
	BiNode *b;

	b = a->right;
	a->right = b->left;
	b->left = a;

	return b;
}

BiNode *LR(BiNode *a){
	a->left = RR(a->left);
	return LL(a);
}

BiNode *RL(BiNode *a){
	a->right = LL(a->right);
	return RR(a);
}

BiNode *insertNode(BiNode *root, int num){
	if(root==NULL){
		root = new BiNode(num);
		return root;
	}
	else if(num<root->value){
		root->left = insertNode(root->left, num);
		if(!isBalanced(root)){
			//LL
			if(num<root->left->value){
				root = LL(root);
			}
			//LR
			else{
				root = LR(root);
			}
		}
	}
	else{
		root->right = insertNode(root->right, num);
		if(!isBalanced(root)){
			//RL
			if(num<root->right->value){
				root = RL(root);
			}
			//RR
			else{
				root = RR(root);
			}
		}
	}

	return root;
}

int main(){
	int n;
	BiNode *head = NULL;

	cin >> n;

	for(int i=0; i<n; i++){
		int num;
		cin >> num;
		head = insertNode(head, num);
	}

	cout << head->value;

	system("pause");
	return 0;
}