//1036. Boys vs Girls
/*
This time you are asked to tell the difference between the lowest grade of all the male students and the highest grade of all the female students.

Input Specification:

Each input file contains one test case. Each case contains a positive integer N, followed by N lines of student information. Each line contains a student's name, gender, ID and grade, separated by a space, where name and ID are strings of no more than 10 characters with no space, gender is either F (female) or M (male), and grade is an integer between 0 and 100. It is guaranteed that all the grades are distinct.

Output Specification:

For each test case, output in 3 lines. The first line gives the name and ID of the female student with the highest grade, and the second line gives that of the male student with the lowest grade. The third line gives the difference gradeF-gradeM. If one such kind of student is missing, output "Absent" in the corresponding line, and output "NA" in the third line instead.

Sample Input 1:

3
Joe M Math990112 89
Mike M CS991301 100
Mary F EE990830 95
Sample Output 1:
Mary EE990830
Joe Math990112
6
Sample Input 2:
1
Jean M AA980920 60
Sample Output 2:
Absent
Jean AA980920
NA
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef struct{
	string name;
	string id;
	int grade;
}student;

bool cmpF(student s1, student s2){
	return s1.grade>s2.grade;
}

bool cmpM(student s1, student s2){
	return s1.grade<s2.grade;
}

int main(int argc, char const *argv[])
{
	vector<student> male, female;
	int n;

	cin >> n;
	for(int i=0; i<n; i++){
		student tmp;
		char ch;
		cin >> tmp.name >> ch >> tmp.id >> tmp.grade;
		if(ch=='F'){
			female.push_back(tmp);
		}
		else{
			male.push_back(tmp);
		}
	}
	sort(female.begin(), female.end(), cmpF);
	sort(male.begin(), male.end(), cmpM);

	bool flag = true;
	if(female.size()==0){
		cout << "Absent";
		flag = false;
	}
	else{
		cout << female[0].name << " " << female[0].id;
	}
	cout << endl;
	if(male.size()==0){
		cout << "Absent";
		flag = false;
	}
	else{
		cout << male[0].name << " " << male[0].id;
	}
	cout << endl;
	if(flag){
		cout << female[0].grade-male[0].grade;
	}
	else{
		cout << "NA";
	}

	system("pause");
	return 0;
}