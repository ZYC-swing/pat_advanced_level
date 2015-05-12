//1063. Set Similarity
/*
Given two sets of integers, the similarity of the sets is defined to be Nc/Nt*100%, where Nc is the number of distinct common numbers shared by the two sets, and Nt is the total number of distinct numbers in the two sets. Your job is to calculate the similarity of any given pair of sets.

Input Specification:

Each input file contains one test case. Each case first gives a positive integer N (<=50) which is the total number of sets. Then N lines follow, each gives a set with a positive M (<=104) and followed by M integers in the range [0, 109]. After the input of sets, a positive integer K (<=2000) is given, followed by K lines of queries. Each query gives a pair of set numbers (the sets are numbered from 1 to N). All the numbers in a line are separated by a space.

Output Specification:

For each query, print in one line the similarity of the sets, in the percentage form accurate up to 1 decimal place.

Sample Input:
3
3 99 87 101
4 87 101 5 87
7 99 101 18 5 135 18 99
2
1 2
1 3
Sample Output:
50.0%
33.3%
*/
#include <iostream>
#include <set>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char const *argv[])
{
	vector<set<int>> sets;
	int n,k;

	scanf("%d", &n);
	sets.resize(n);
	for(int i=0; i<n; i++){
		int m;
		scanf("%d", &m);
		for(int j=0; j<m; j++){
			int num;
			scanf("%d", &num);
			sets[i].insert(num);
		}
	}

	scanf("%d", &k);
	for(int i=0; i<k; i++){
		int s[2],cnt[2],totalCnt;
		float rate = 100.0;
		set<int> tmp;

		scanf("%d%d", &s[0], &s[1]);
		for(int j=0; j<2; j++){
			s[j] -= 1;
			cnt[j] = sets[s[j]].size();
		}

		totalCnt = cnt[0];
		for(set<int>::iterator it=sets[s[1]].begin(); it!=sets[s[1]].end(); it++){
			if(sets[s[0]].find(*it)==sets[s[0]].end()){
				totalCnt++;
			}
		}

		rate *= (cnt[0]+cnt[1])*1.0/totalCnt-1;
		printf("%.1f%%\n", rate);
	}

	system("pause");
	return 0;
}