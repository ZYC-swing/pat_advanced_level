//1052. Linked List Sorting
/*
A linked list consists of a series of structures, which are not necessarily adjacent in memory. We assume that each structure contains an integer key and a Next pointer to the next structure. Now given a linked list, you are supposed to sort the structures according to their key values in increasing order.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive N (< 105) and an address of the head node, where N is the total number of nodes in memory and the address of a node is a 5-digit positive integer. NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Key Next

where Address is the address of the node in memory, Key is an integer in [-105, 105], and Next is the address of the next node. It is guaranteed that all the keys are distinct and there is no cycle in the linked list starting from the head node.

Output Specification:

For each test case, the output format is the same as that of the input, where N is the total number of nodes in the list and all the nodes must be sorted order.

Sample Input:
5 00001
11111 100 -1
00001 0 22222
33333 100000 11111
12345 -1 33333
22222 1000 12345
Sample Output:
5 12345
12345 -1 00001
00001 0 11111
11111 100 22222
22222 1000 33333
33333 100000 -1
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

typedef struct{
	int addr;
	int key;
	int nextAddr;
}node;

bool cmp(node n1, node n2){
	return n1.key<n2.key;
}

int main(int argc, char const *argv[])
{
	int n,head;
	map<int,pair<int,int>> mm;
	vector<node> validList;

	cin >> n >> head;

	if(head==-1){
		cout << "0 -1";
		system("pause");
		return 0;
	}
	for(int i=0; i<n; i++){
		int addr[2],key;
		cin >> addr[0] >> key >> addr[1];
		mm[addr[0]] = pair<int,int>(key,addr[1]);
	}

	int index = head;
	while(index!=-1){
		node tmp;
		tmp.addr = index;
		tmp.key = mm[index].first;
		tmp.nextAddr = mm[index].second;
		validList.push_back(tmp);
		index = mm[index].second;
	}

	sort(validList.begin(),validList.end(),cmp);

	printf("%d %05d\n", validList.size(), validList[0].addr);
	for(int i=0; i<validList.size(); i++){
		printf("%05d %d ", validList[i].addr, validList[i].key);
		if(i==validList.size()-1){
			printf("-1\n");
		}
		else{
			printf("%05d\n", validList[i+1].addr);
		}
	}

	system("pause");
	return 0;
}