//1028. List Sorting
/*
Excel can sort records according to any column. Now you are supposed to imitate this function.

Input

Each input file contains one test case. For each case, the first line contains two integers N (<=100000) and C, where N is the number of records and C is the column that you are supposed to sort the records with. Then N lines follow, each contains a record of a student. A student's record consists of his or her distinct ID (a 6-digit number), name (a string with no more than 8 characters without space), and grade (an integer between 0 and 100, inclusive).

Output

For each test case, output the sorting result in N lines. That is, if C = 1 then the records must be sorted in increasing order according to ID's; if C = 2 then the records must be sorted in non-decreasing order according to names; and if C = 3 then the records must be sorted in non-decreasing order according to grades. If there are several students who have the same name or grade, they must be sorted according to their ID's in increasing order.

Sample Input 1
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
Sample Output 1
000001 Zoe 60
000007 James 85
000010 Amy 90
Sample Input 2
4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98
Sample Output 2
000010 Amy 90
000002 James 98
000007 James 85
000001 Zoe 60
Sample Input 3
4 3
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 90
Sample Output 3
000001 Zoe 60
000007 James 85
000002 James 90
000010 Amy 90
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
	int id;
	char name[9];
	int grade;
}record;

bool cmpId(record r1, record r2){
	return r1.id<r2.id;
}

bool cmpName(record r1, record r2){
	if(strcmp(r1.name,r2.name)==0){
		return cmpId(r1,r2);
	}
	else if(strcmp(r1.name,r2.name)<0){
		return 1;
	}
	else{
		return 0;
	}
}

bool cmpGrade(record r1, record r2){
	if(r1.grade==r2.grade){
		return cmpId(r1,r2);
	}
	else{
		return r1.grade<r2.grade;
	}
}

int main(int argc, char const *argv[])
{
	int n,c;
	vector<record> records;
	record tmp;

	cin >> n >> c;
	while(n--){
		scanf("%d%s%d", &tmp.id, tmp.name, &tmp.grade);
		records.push_back(tmp);
	}

	switch(c){
		case 1:
			sort(records.begin(),records.end(),cmpId);
			break;
		case 2:
			sort(records.begin(),records.end(),cmpName);
			break;
		case 3:
			sort(records.begin(),records.end(),cmpGrade);
			break;
		default:
			break;
	}

	for (vector<record>::iterator it=records.begin(); it!=records.end(); it++)
	{
		printf("%06d %s %d\n", (*it).id, (*it).name, (*it).grade);
	}

	system("pause");
	return 0;
}