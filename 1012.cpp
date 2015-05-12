//1012. The Best Rank
/*
To evaluate the performance of our first year CS majored students, we consider their grades of three courses only: C - C Programming Language, M - Mathematics (Calculus or Linear Algebra), and E - English. At the mean time, we encourage students by emphasizing on their best ranks -- that is, among the four ranks with respect to the three courses and the average grade, we print the best rank for each student.

For example, The grades of C, M, E and A - Average of 4 students are given as the following:

StudentID  C  M  E  A
310101     98 85 88 90
310102     70 95 88 84
310103     82 87 94 88
310104     91 91 91 91
Then the best ranks for all the students are No.1 since the 1st one has done the best in C Programming Language, while the 2nd one in Mathematics, the 3rd one in English, and the last one in average.

Input

Each input file contains one test case. Each case starts with a line containing 2 numbers N and M (<=2000), which are the total number of students, and the number of students who would check their ranks, respectively. Then N lines follow, each contains a student ID which is a string of 6 digits, followed by the three integer grades (in the range of [0, 100]) of that student in the order of C, M and E. Then there are M lines, each containing a student ID.

Output

For each of the M students, print in one line the best rank for him/her, and the symbol of the corresponding rank, separated by a space.

The priorities of the ranking methods are ordered as A > C > M > E. Hence if there are two or more ways for a student to obtain the same best rank, output the one with the highest priority.

If a student is not on the grading list, simply output "N/A".

Sample Input
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
Sample Output
1 C
1 M
1 E
1 A
3 A
N/A
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iterator>
using namespace std;

#define MAXN 2000

typedef struct{
	string id;
	int c;
	int math;
	int e;
	int a;
	int bestRank;
	char bestLable;
}record;

bool cmp(int a, int b){
	return a>b;
}

int main(){
	int n,m,index;
	int c[MAXN],math[MAXN],e[MAXN],a[MAXN];
	bool valid[1000000];
	vector<record> records;
	record tmp;
	string id;

	memset(valid,0,sizeof(valid));

	//输入
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> id;
		index = atoi(id.c_str());
		valid[index] = true;
		tmp.id = id;
		cin >> c[i] >> math[i] >> e[i];
		tmp.c = c[i];
		tmp.math = math[i];
		tmp.e = e[i];
		tmp.a = a[i] = (c[i]+math[i]+e[i])/3;
		records.push_back(tmp);
	}
	
	//排序
	sort(c,c+n,cmp);
	sort(math,math+n,cmp);
	sort(e,e+n,cmp);
	sort(a,a+n,cmp);
	for(vector<record>::iterator it=records.begin(); it!=records.end(); it++){
		(*it).bestRank = n;
		(*it).bestLable = 'E';
		for(int i=0; i<n; i++){
			if(e[i] == (*it).e){
				if(i+1<=(*it).bestRank){
					(*it).bestRank = i+1;
					(*it).bestLable = 'E';
				}
				break;
			}
		}
		for(int i=0; i<n; i++){
			if(math[i] == (*it).math){
				if(i+1<=(*it).bestRank){
					(*it).bestRank = i+1;
					(*it).bestLable = 'M';
				}
				break;
			}
		}
		for(int i=0; i<n; i++){
			if(c[i] == (*it).c){
				if(i+1<=(*it).bestRank){
					(*it).bestRank = i+1;
					(*it).bestLable = 'C';
				}
				break;
			}
		}
		for(int i=0; i<n; i++){
			if(a[i] == (*it).a){
				if(i+1<=(*it).bestRank){
					(*it).bestRank = i+1;
					(*it).bestLable = 'A';
				}
				break;
			}
		}
	}

	//输出
	for(int i=0; i<m; i++){
		cin >> id;
		index = atoi(id.c_str());
		if(valid[index]){
			for(vector<record>::iterator it=records.begin(); it!=records.end(); it++){
				if((*it).id == id){
					cout << (*it).bestRank << " " << (*it).bestLable;
					break;
				}
			}
		}
		else{
			cout << "N/A";
		}
		if(i!=m-1)
			cout << endl;
	}

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct info{
	int id;
	double A;
	int C;
	int M;
	int E;
	int bestRank;
	char bestLabel;
	info() : bestRank(2001){}
};

bool cmpA(info i1, info i2){
	return i1.A > i2.A;
}

bool cmpC(info i1, info i2){
	return i1.C > i2.C;
}

bool cmpM(info i1, info i2){
	return i1.M > i2.M;
}

bool cmpE(info i1, info i2){
	return i1.E > i2.E;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<info> infos(n);
	map<int, info> mm;
	for (int i = 0; i < n; ++i){
		cin >> infos[i].id >> infos[i].C >> infos[i].M >> infos[i].E;
		infos[i].A = (infos[i].C + infos[i].M + infos[i].E) * 1.0 / 3;
	}
	int tmpRank;
	sort(infos.begin(), infos.end(), cmpA);
	for (int i = 0, preScore = 101; i < n; ++i){
		if (infos[i].A < preScore){
			preScore = infos[i].A;
			tmpRank = i + 1;
		}
		if (tmpRank < infos[i].bestRank){
			infos[i].bestLabel = 'A';
			infos[i].bestRank = tmpRank;
		}
	}
	sort(infos.begin(), infos.end(), cmpC);
	for (int i = 0, preScore = 101; i < n; ++i){
		if (infos[i].C < preScore){
			preScore = infos[i].C;
			tmpRank = i + 1;
		}
		if (tmpRank < infos[i].bestRank){
			infos[i].bestLabel = 'C';
			infos[i].bestRank = tmpRank;
		}
	}
	sort(infos.begin(), infos.end(), cmpM);
	for (int i = 0, preScore = 101; i < n; ++i){
		if (infos[i].M < preScore){
			preScore = infos[i].M;
			tmpRank = i + 1;
		}
		if (tmpRank < infos[i].bestRank){
			infos[i].bestLabel = 'M';
			infos[i].bestRank = tmpRank;
		}
	}
	sort(infos.begin(), infos.end(), cmpE);
	for (int i = 0, preScore = 101; i < n; ++i){
		if (infos[i].E < preScore){
			preScore = infos[i].E;
			tmpRank = i + 1;
		}
		if (tmpRank < infos[i].bestRank){
			infos[i].bestLabel = 'E';
			infos[i].bestRank = tmpRank;
		}
	}
	for (int i = 0; i < n; ++i){
		mm[infos[i].id] = infos[i];
	}
	int queryId;
	for (int i = 0; i < m; ++i){
		cin >> queryId;
		auto tmp = mm.find(queryId);
		if (tmp == mm.end()){
			cout << "N/A";
		}
		else{
			cout << tmp->second.bestRank << " " << tmp->second.bestLabel;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}