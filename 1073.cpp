//1073. Scientific Notation
/*
Scientific notation is the way that scientists easily handle very large numbers or very small numbers. The notation matches the regular expression [+-][1-9]"."[0-9]+E[+-][0-9]+ which means that the integer portion has exactly one digit, there is at least one digit in the fractional portion, and the number and its exponent's signs are always provided even when they are positive.

Now given a real number A in scientific notation, you are supposed to print A in the conventional notation while keeping all the significant figures.

Input Specification:

Each input file contains one test case. For each case, there is one line containing the real number A in scientific notation. The number is no more than 9999 bytes in length and the exponent's absolute value is no more than 9999.

Output Specification:

For each test case, print in one line the input number A in the conventional notation, with all the significant figures kept, including trailing zeros,

Sample Input 1:
+1.23400E-03
Sample Output 1:
0.00123400
Sample Input 2:
-1.2E+10
Sample Output 2:
-12000000000
*/
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	string rawNum,num;
	int e = 0,sign[2];

	cin >> rawNum;
	sign[0] = (rawNum[0]=='+')?1:-1;

	int index = 1;
	while(rawNum[index]!='E'){
		index++;
	}
	num.assign(rawNum,1,index-1);
	sign[1] = (rawNum[++index]=='+')?1:-1;
	index++;
	for(; index<rawNum.length(); index++){
		e = e*10+rawNum[index]-'0';
	}

	if(sign[0]<0){
		cout << '-';
	}
	num.erase(num.begin()+1);
	if(sign[1]==1){
		//末尾要补零
		if(e>=num.length()-1){
			string zeros(e-num.length()+1,'0');
			num.append(zeros);
			cout << num;
		}
		else{
			string before,after;
			before.assign(num.begin(), num.begin()+e+1);
			after.assign(num.begin()+e+1,num.end());
			cout << before << '.' << after;
		}
	}
	else{
		string zeros(e-1,'0');
		zeros.append(num);
		cout << "0." << zeros;
	}

	system("pause");
	return 0;
}