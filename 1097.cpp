//1097. Deduplication on a Linked List
/*
Given a singly linked list L with integer keys, you are supposed to remove the nodes with duplicated absolute values of the keys. That is, for each value K, only the first node of which the value or absolute value of its key equals K will be kept. At the mean time, all the removed nodes must be kept in a separate list. For example, given L being 21→-15→-15→-7→15, you must output 21→-15→-7, and the removed list -15→15.

Input Specification:

Each input file contains one test case. For each case, the first line contains the address of the first node, and a positive N (<= 105) which is the total number of nodes. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Key Next

where Address is the position of the node, Key is an integer of which absolute value is no more than 104, and Next is the position of the next node.

Output Specification:

For each case, output the resulting linked list first, then the removed list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 5
99999 -7 87654
23854 -15 00000
87654 15 -1
00000 -15 99999
00100 21 23854
Sample Output:
00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
using namespace std;

struct node{
	int addr;
	int key;
	int next;
};

int main(){
	int head, n;
	cin >> head >> n;
	map<int, node> input;
	set<int> appeared;
	vector<node> list[2];
	for (int i = 0; i < n; ++i){
		int from, to, key;
		cin >> from >> key >> to;
		input[from].addr = from;
		input[from].key = key;
		input[from].next = to;
	}
	int index = head;
	while (index != -1 && input.find(index) != input.end()){
		int value = abs(input[index].key);
		if (appeared.find(value) == appeared.end()){
			appeared.insert(value);
			list[0].push_back(input[index]);
		}
		else{
			list[1].push_back(input[index]);
		}
		index = input[index].next;
	}
	for (int k = 0; k < 2; ++k){
		for (int i = 0; i < list[k].size(); ++i){
			printf("%05d %d ", list[k][i].addr, list[k][i].key);
			if (i < list[k].size() - 1){
				printf("%05d\n", list[k][i + 1].addr);
			}
			else{
				printf("-1\n");
			}
		}
	}
	system("pause");
	return 0;
}