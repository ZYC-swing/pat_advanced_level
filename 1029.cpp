//1029. Median
/*
Given an increasing sequence S of N integers, the median is the number at the middle position. For example, the median of S1={11, 12, 13, 14} is 12, and the median of S2={9, 10, 15, 16, 17} is 15. The median of two sequences is defined to be the median of the nondecreasing sequence which contains all the elements of both sequences. For example, the median of S1 and S2 is 13.

Given two increasing sequences of integers, you are asked to find their median.

Input

Each input file contains one test case. Each case occupies 2 lines, each gives the information of a sequence. For each sequence, the first positive integer N (<=1000000) is the size of that sequence. Then N integers follow, separated by a space. It is guaranteed that all the integers are in the range of long int.

Output

For each test case you should output the median of the two given sequences in a line.

Sample Input
4 11 12 13 14
5 9 10 15 16 17
Sample Output
13
*/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char const *argv[])
{
	vector<long long> seq[2];
	long long num;
	int len[2];

	for(int i=0; i<2; i++){
		scanf("%d", &len[i]);
		for(int j=0; j<len[i]; j++){
			scanf("%ld", &num);
			seq[i].push_back(num);
		}
	}

	int cnt = 0;
	int mid = (len[0]+len[1]+1)/2;
	int index[2] = {0,0};
	long long tmp;
	int flag;
	while(cnt!=mid && index[0]<len[0] && index[1]<len[1]){
		flag = (seq[0][index[0]]<seq[1][index[1]])?0:1;
		tmp = seq[flag][index[flag]];
		index[flag]++;
		cnt++;
	}

	if(cnt!=mid){
		flag = (index[0]==len[0])?1:0;
		tmp = seq[flag][index[flag]+mid-cnt-1];
	}

	cout << tmp;

	system("pause");
	return 0;
}