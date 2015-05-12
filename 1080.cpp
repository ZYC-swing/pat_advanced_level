//1080. Graduate Admission
/*
It is said that in 2013, there were about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province. It would help a lot if you could write a program to automate the admission procedure.

Each applicant will have to provide two grades: the national entrance exam grade GE, and the interview grade GI. The final grade of an applicant is (GE + GI) / 2. The admission rules are:

The applicants are ranked according to their final grades, and will be admitted one by one from the top of the rank list.
If there is a tied final grade, the applicants will be ranked according to their national entrance exam grade GE. If still tied, their ranks must be the same.
Each applicant may have K choices and the admission will be done according to his/her choices: if according to the rank list, it is one's turn to be admitted; and if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this school, or one's other choices will be considered one by one in order. If one gets rejected by all of preferred schools, then this unfortunate applicant will be rejected.
If there is a tied rank, and if the corresponding applicants are applying to the same school, then that school must admit all the applicants with the same rank, even if its quota will be exceeded.
Input Specification:

Each input file contains one test case. Each case starts with a line containing three positive integers: N (<=40,000), the total number of applicants; M (<=100), the total number of graduate schools; and K (<=5), the number of choices an applicant may have.

In the next line, separated by a space, there are M positive integers. The i-th integer is the quota of the i-th graduate school respectively.

Then N lines follow, each contains 2+K integers separated by a space. The first 2 integers are the applicant's GE and GI, respectively. The next K integers represent the preferred schools. For the sake of simplicity, we assume that the schools are numbered from 0 to M-1, and the applicants are numbered from 0 to N-1.

Output Specification:

For each test case you should output the admission results for all the graduate schools. The results of each school must occupy a line, which contains the applicants' numbers that school admits. The numbers must be in increasing order and be separated by a space. There must be no extra space at the end of each line. If no applicant is admitted by a school, you must output an empty line correspondingly.

Sample Input:
11 6 3
2 1 2 2 2 3
100 100 0 1 2
60 60 2 3 5
100 90 0 3 4
90 100 1 2 0
90 90 5 1 3
80 90 1 0 2
80 80 0 1 2
80 80 0 1 2
80 70 1 3 2
70 80 1 2 3
100 100 0 2 4
Sample Output:
0 10
3
5 6 7
2 8

1 4
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
	int id;
	int ge;
	int gi;
	int total;
	int rank;
	vector<int> schools;
}applicant;

typedef struct{
	int quota;
	vector<int> ids;
	int lowestRank;//已录取的最低名次
}school;

bool cmp(applicant a1, applicant a2){
	if(a1.total>a2.total){
		return 1;
	}
	else if(a1.total==a2.total && a1.ge>a2.ge){
		return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	vector<applicant> applicants;
	vector<school> schools;
	int n,m,k;

	cin >> n >> m >> k;
	applicants.resize(n);
	schools.resize(m);
	for(int i=0; i<n; i++){
		applicants[i].schools.resize(k);
	}
	for(int i=0; i<m; i++){
		cin >> schools[i].quota;
		schools[i].lowestRank = 1;
	}
	for(int i=0; i<n; i++){
		cin >> applicants[i].ge >> applicants[i].gi;
		applicants[i].total = applicants[i].ge+applicants[i].gi;
		applicants[i].id = i;
		for(int j=0; j<k; j++){
			cin >> applicants[i].schools[j];
		}
	}
	sort(applicants.begin(),applicants.end(),cmp);
	
	int tmpRank,tmpGe,tmpTotal;
	tmpRank = 0;
	tmpGe = 101;
	tmpTotal = 201;
	for(int i=0; i<n; i++){
		if(!(applicants[i].total==tmpTotal && applicants[i].ge==tmpGe)){
			tmpRank = i+1;
			tmpGe = applicants[i].ge;
			tmpTotal = applicants[i].total;
		}
		applicants[i].rank = tmpRank;

		//看所选的学校能否入取
		for(int j=0; j<k; j++){
			int sid = applicants[i].schools[j];
			if(schools[sid].ids.size()<schools[sid].quota){
				schools[sid].ids.push_back(applicants[i].id);
				schools[sid].lowestRank = applicants[i].rank;
				break;
			}
			else if(schools[sid].lowestRank==applicants[i].rank){
				schools[sid].ids.push_back(applicants[i].id);
				break;
			}
		}
	}

	for(int i=0; i<m; i++){
		sort(schools[i].ids.begin(),schools[i].ids.end());
		for(int j=0; j<schools[i].ids.size(); j++){
			cout << schools[i].ids[j];
			if(j<schools[i].ids.size()-1){
				cout << " ";
			}
		}
		cout << endl;
	}

	system("pause");
	return 0;
}