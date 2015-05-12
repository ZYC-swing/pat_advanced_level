//1060. Are They Equal
/*
If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered equal since they are both saved as 0.123*105 with simple chopping. Now given the number of significant digits on a machine and two float numbers, you are supposed to tell if they are treated equal in that machine.

Input Specification:

Each input file contains one test case which gives three numbers N, A and B, where N (<100) is the number of significant digits, and A and B are the two float numbers to be compared. Each float number is non-negative, no greater than 10100, and that its total digit number is less than 100.

Output Specification:

For each test case, print in a line "YES" if the two numbers are treated equal, and then the number in the standard form "0.d1...dN*10^k" (d1>0 unless the number is 0); or "NO" if they are not treated equal, and then the two numbers in their standard form. All the terms must be separated by a space, with no extra space at the end of a line.

Note: Simple chopping is assumed without rounding.

Sample Input 1:
3 12300 12358.9
Sample Output 1:
YES 0.123*10^5
Sample Input 2:
3 120 128
Sample Output 2:
NO 0.120*10^3 0.128*10^3
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	string num[2],valid[2];
	int e[2]={0,0};

	cin >> n >> num[0] >> num[1];
	
	for(int i=0; i<2; i++){
		//删去前面多余的0
		string::iterator it;
		for(it=num[i].begin(); it!=num[i].end() && *it=='0';){
			num[i].erase(it);
		}
		int ex=0;
		while(ex<num[i].length() && (num[i][ex]=='0' || num[i][ex]=='.')){
			ex++;
		}
		if(ex==num[i].length()){
			ex=0;
		}
		else if(ex>0){
			e[i] = 1-ex;
		}
		else{
			while(ex<num[i].length() && num[i][ex]!='.'){
				ex++;
			}
			e[i] = ex;
		}
	}

	for(int i=0; i<2; i++){
		int index=0;
		while(index<num[i].length() && (num[i][index]=='0' || num[i][index]=='.')){
			index++;
		}
		int cnt=0;
		while(index<num[i].length() && cnt<n){
			if(num[i][index]=='.'){
				index++;
			}
			else{
				stringstream ss;
				ss << num[i][index++];
				valid[i].append(ss.str());
				cnt++;
			}
		}
		//原本有效位数不够，需要补0
		while(cnt<n){
			valid[i].append("0");
			cnt++;
		}
	}

	if(valid[0]==valid[1] && e[0]==e[1]){
		cout << "YES";
		cout << " 0." << valid[0] << "*10^" << e[0];
	} 
	else{
		cout << "NO";
		for(int i=0; i<2; i++){
			cout << " 0." << valid[i] << "*10^" << e[i];
		}
	}

	system("pause");
	return 0;
}