//1025. PAT Ranking
/*
Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive number N (<=100), the number of test locations. Then N ranklists follow, each starts with a line containing a positive integer K (<=300), the number of testees, and then K lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

registration_number final_rank location_number local_rank

The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

Sample Input:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
Sample Output:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct
{
	string id;
	int score;
	int final_rank;
	int location_number;
	int local_rank;
}record;

bool cmp(record r1, record r2){
	if(r1.score>r2.score){
		return 1;
	}
	else if(r1.score==r2.score && r1.id<r2.id){
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char const *argv[])
{
	vector<record> local_records,final_records;
	int n,k;

	cin >> n;
	for(int i=1; i<=n; i++){
		local_records.clear();
		cin >> k;
		while(k--){
			record tmp;
			cin >> tmp.id >> tmp.score;
			tmp.location_number = i;
			local_records.push_back(tmp);
		}
		sort(local_records.begin(), local_records.end(), cmp);

		int cnt = 1;
		int preScore = 101;
		int preRank = 0;
		for(vector<record>::iterator it=local_records.begin(); it!=local_records.end(); it++){
			if((*it).score==preScore){
				(*it).local_rank = preRank;
				cnt++;
			}
			else{
				preRank += cnt;
				(*it).local_rank = preRank;
				cnt = 1;
				preScore = (*it).score;
			}
			final_records.push_back(*it);
		}
	}

	sort(final_records.begin(), final_records.end(), cmp);
	int cnt = 1;
	int preScore = 101;
	int preRank = 0;
	cout << final_records.size() << endl;
	for(vector<record>::iterator it=final_records.begin(); it!=final_records.end(); it++){
		if((*it).score==preScore){
			(*it).final_rank = preRank;
			cnt++;
		}
		else{
			preRank += cnt;
			(*it).final_rank = preRank;
			cnt = 1;
			preScore = (*it).score;
		}
		cout << (*it).id << " " << (*it).final_rank << " " << (*it).location_number << " " << (*it).local_rank << endl;
	}

	system("pause");
	return 0;
}