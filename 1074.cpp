//1074. Reversing Linked List
/*
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. For example, given L being 1→2→3→4→5→6, if K = 3, then you must output 3→2→1→6→5→4; if K = 4, you must output 4→3→2→1→5→6.

Input Specification:

Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (<= 105) which is the total number of nodes, and a positive K (<=N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:

For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef struct{
	int addr;
	int value;
	int next;
}node;

int main(int argc, char const *argv[])
{
	int id,n,k;
	vector<node> lis;
	map<int,pair<int,int>> input;

	cin >> id >> n >> k;
	for(int i=0; i<n; i++){
		int addr,value,next;
		cin >> addr >> value >> next;
		input[addr] = pair<int,int>(value,next);
	}

	while(id!=-1){
		node tmp;
		tmp.addr = id;
		tmp.value = input[id].first;
		tmp.next = input[id].second;
		lis.push_back(tmp);
		id = input[id].second;
	}

	int left,right;
	left = 0;
	right = k;
	while(right<=lis.size()){
		reverse(lis.begin()+left,lis.begin()+right);
		left = right;
		right = left+k;
	}

	for(int i=0; i<lis.size(); i++){
		printf("%05d %d ", lis[i].addr, lis[i].value);
		if(i<lis.size()-1){
			printf("%05d\n", lis[i+1].addr);
		}
		else{
			cout << -1;
		}
	}

	system("pause");
	return 0;
}