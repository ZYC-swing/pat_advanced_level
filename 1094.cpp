//1094. The Largest Generation
/*
A family hierarchy is usually presented by a pedigree tree where all the nodes on the same level belong to the same generation. Your task is to find the generation with the largest population.

Input Specification:

Each input file contains one test case. Each case starts with two positive integers N (<100) which is the total number of family members in the tree (and hence assume that all the members are numbered from 01 to N), and M (<N) which is the number of family members who have children. Then M lines follow, each contains the information of a family member in the following format:

ID K ID[1] ID[2] ... ID[K]

where ID is a two-digit number representing a family member, K (>0) is the number of his/her children, followed by a sequence of two-digit ID's of his/her children. For the sake of simplicity, let us fix the root ID to be 01. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the largest population number and the level of the corresponding generation. It is assumed that such a generation is unique, and the root level is defined to be 1.

Sample Input:
23 13
21 1 23
01 4 03 02 04 05
03 3 06 07 08
06 2 12 13
13 1 21
08 2 15 16
02 2 09 10
11 2 19 20
17 1 22
05 1 11
07 1 14
09 1 17
10 1 18
Sample Output:
9 4
*/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
using namespace std;

int main(){
	int n, m;
	cin >> n >> m;

	map<int, vector<int>> nonLeafNodes;
	vector<int> levelCnt(n + 1, 0);
	for (int i = 0; i < m; ++i){
		int index, k;
		cin >> index >> k;
		for (int j = 0; j < k; ++j){
			int tmp;
			cin >> tmp;
			nonLeafNodes[index].push_back(tmp);
		}
	}
	queue<pair<int, int>> qq;
	qq.push(make_pair(1, 1));
	int resLevel, maxCnt = 0;
	while (!qq.empty()){
		auto tmp = qq.front();
		qq.pop();
		if (++levelCnt[tmp.second] > maxCnt){
			maxCnt = levelCnt[tmp.second];
			resLevel = tmp.second;
		}
		if (nonLeafNodes.find(tmp.first) != nonLeafNodes.end()){
			for (auto i : nonLeafNodes[tmp.first]){
				qq.push(make_pair(i, tmp.second + 1));
			}
		}
	}
	cout << maxCnt << " " << resLevel;
	system("pause");
	return 0;
}