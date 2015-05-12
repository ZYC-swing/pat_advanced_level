//1001.A+B Format
/*
Calculate a + b and output the sum in standard format -- that is, the digits must be separated into groups of three by commas (unless there are less than four digits).

Input

Each input file contains one test case. Each case contains a pair of integers a and b where -1000000 <= a, b <= 1000000. The numbers are separated by a space.

Output

For each test case, you should output the sum of a and b in one line. The sum must be written in the standard format.

Sample Input
-1000000 9
Sample Output
-999,991
*/
#include <iostream>
using namespace std;

void print(int num){
	int tmp1 = num/1000;
	int tmp2 = num%1000;
	if(tmp1>0){
		print(tmp1);
		cout << ',';
		if(tmp2/100>0)//处理百位
			cout << tmp2;
		else{//百位为0时处理十位和个位
			cout << '0';
			if((tmp2%100)/10>0)
				cout << (tmp2%100)/10;
			else
				cout << '0';
			cout << tmp2%10;//个位
		}
	}
	else{
		cout << tmp2;
	}
}

int main(){
	int a,b,sum;

	cin >> a >> b;

	sum = a+b;
	if(sum<0){
		cout << '-';
		sum = -sum;
	}
	print(sum);

	system("pause");
	return 0;
}