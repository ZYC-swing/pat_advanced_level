//1004.Counting Leaves
/*
A family hierarchy is usually presented by a pedigree tree. Your job is to count those family members who have no child.
Input

Each input file contains one test case. Each case starts with a line containing 0 < N < 100, the number of nodes in a tree, and M (< N), the number of non-leaf nodes. Then M lines follow, each in the format:

ID K ID[1] ID[2] ... ID[K]
where ID is a two-digit number representing a given non-leaf node, K is the number of its children, followed by a sequence of two-digit ID's of its children. For the sake of simplicity, let us fix the root ID to be 01.
Output

For each test case, you are supposed to count those family members who have no child for every seniority level starting from the root. The numbers must be printed in a line, separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where 01 is the root and 02 is its only child. Hence on the root 01 level, there is 0 leaf node; and on the next level, there is 1 leaf node. Then we should output "0 1" in a line.

Sample Input
2 1
01 1 02
Sample Output
0 1
*/
#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <iterator>
using namespace std;

typedef struct{
	int k;
	list<int> ids;
}NonLeafNode;

NonLeafNode node[100];
int level[100],flag[100];//每个节点的层号、每个节点是否是非叶节点（1代表非叶节点，0是叶节点）

void setLevel(int id){
	for(list<int>::iterator it=node[id].ids.begin(); it!=node[id].ids.end(); it++){
		int child_id = *it;
		level[child_id] = level[id]+1;
		if(flag[child_id])
			setLevel(child_id);
	}
}

int main(){
	int n,m;
	
	memset(level,-1,sizeof(level));
	memset(flag,0,sizeof(flag));

	cin >> n >> m;
	for(int i=0; i<m; i++){
		int id;
		int child_id;
		int k;
		cin >> id >> k;
		flag[id]=1;
		node[id].k=k;
		for(int j=0; j<k; j++){
			cin >> child_id;
			node[id].ids.push_back(child_id);
		}
	}

	level[1]=0;
	setLevel(1);

	int levelCnt[100];
	memset(levelCnt,0,sizeof(levelCnt));
	int maxLevel=0;
	for(int i=1;i<100;i++){
		if(level[i]!=-1 && !flag[i]){
			levelCnt[level[i]]++;
			if(level[i]>maxLevel)
				maxLevel=level[i];
		}
	}

	cout << levelCnt[0];
	for(int i=1; i<=maxLevel; i++)
		cout << " " << levelCnt[i];
	
	system("pause");
	return 0;
}


//第二次刷
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int main(){
	int n, m;
	map<int, vector<int>> nodes;
	queue<pair<int, int>> qq;
	vector<int> levelCnt;
	cin >> n >> m;
	int id, k;
	for (int i = 0; i < m; ++i){
		cin >> id >> k;
		int tmp;
		while (k--){
			cin >> tmp;
			nodes[id].push_back(tmp);
		}
	}
	qq.push(make_pair(1, 1));
	while (!qq.empty()){
		auto tmp = qq.front();
		qq.pop();
		if (levelCnt.size() < tmp.second){
			levelCnt.push_back(0);
		}
		if (nodes.find(tmp.first) == nodes.end()){
			++levelCnt[tmp.second - 1];
		}
		else{
			for (auto i : nodes[tmp.first]){
				qq.push(make_pair(i, tmp.second + 1));
			}
		}
	}
	for (int i = 0; i < levelCnt.size(); ++i){
		if (i){
			cout << " ";
		}
		cout << levelCnt[i];
	}
	system("pause");
	return 0;
}