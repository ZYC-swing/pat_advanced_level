//1065. A+B and C (64bit)
/*
Given three integers A, B and C in [-2^63, 2^63], you are supposed to tell whether A+B > C.

Input Specification:

The first line of the input gives the positive number of test cases, T (<=10). Then T test cases follow, each consists of a single line containing three integers A, B and C, separated by single spaces.

Output Specification:

For each test case, output in one line "Case #X: true" if A+B>C, or "Case #X: false" otherwise, where X is the case number (starting from 1).

Sample Input:
3
1 2 3
2 3 4
9223372036854775807 -9223372036854775808 0
Sample Output:
Case #1: false
Case #2: true
Case #3: false
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	long long a,b,c;
	int t;

	cin >> t;
	for(int i=1; i<=t; i++){
		cin >> a >> b >> c;
		cout << "Case #" << i << ": ";
		if((a>=0 && b<=0) || (a<=0 && b>=0)){
			if(a+b>c){
				cout << "true" << endl;
			}
			else{
				cout << "false" << endl;
			}
		}
		else if(a>0){
			if(a+b<a){
				cout << "true" << endl;
			}
			else if(a+b>c){
				cout << "true" << endl;
			}
			else{
				cout << "false" << endl;
			}
		}
		else if(a<0){
			if(a+b>a){
				cout << "false" << endl;
			}
			else if(a+b>c){
				cout << "true" << endl;
			}
			else{
				cout << "false" << endl;
			}
		}
	}
	system("pause");
	return 0;
}