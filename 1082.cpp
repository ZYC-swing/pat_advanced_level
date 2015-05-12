//1082. Read Number in Chinese
/*
Given an integer with no more than 9 digits, you are supposed to read it in the traditional Chinese way. Output "Fu" first if it is negative. For example, -123456789 is read as "Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu". Note: zero ("ling") must be handled correctly according to the Chinese tradition. For example, 100800 is "yi Shi Wan ling ba Bai".

Input Specification:

Each input file contains one test case, which gives an integer with no more than 9 digits.

Output Specification:

For each test case, print in a line the Chinese way of reading the number. The characters are separated by a space and there must be no extra space at the end of the line.

Sample Input 1:
-123456789
Sample Output 1:
Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu
Sample Input 2:
100800
Sample Output 2:
yi Shi Wan ling ba Bai
*/
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

string digit[10]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};

string readDigits(int cnt, int num, bool flag, bool zf){
	if(num==0){
		return "";
	}
	string str;
	if(flag){
		str = " ";
	}
	else{
		str = "";
	}
	switch(cnt){
		case 4:
			if(num/1000){
				str.append(digit[num/1000]);
				str.append(" Qian");
				str.append(readDigits(3,num%1000,true,zf));
			}
			else{
				if(flag){
					str.append(digit[0]);
					zf = true;
				}
				str.append(readDigits(3,num%1000,flag,zf));
			}
			break;
		case 3:
			if(num/100){
				str.append(digit[num/100]);
				str.append(" Bai");
				str.append(readDigits(2,num%100,true,zf));
			}
			else{
				if(flag && !zf){
					str.append(digit[0]);
					zf = true;
				}
				else{
					str = "";
				}
				str.append(readDigits(2,num%100,flag,zf));
			}
			break;
		case 2:
			if(num/10){
				str.append(digit[num/10]);
				str.append(" Shi");
				str.append(readDigits(1,num%10,true,zf));
			}
			else{
				if(flag && !zf){
					str.append(digit[0]);
					zf = true;
				}
				else{
					str = "";
				}
				str.append(readDigits(1,num%10,flag,zf));
			}
			break;
		case 1:
			str.append(digit[num]);
			break;
		default:
			break;
	}

	return str;
}

int main(int argc, char const *argv[])
{
	long long num;
	bool flag = false;

	cin >> num;
	if(num<0){
		cout << "Fu ";
		num = -num;
	}
	if(num/100000000!=0){
		cout << digit[num/100000000] << " Yi";
		num %= 100000000;
		flag = true;
	}
	if(num/10000!=0){
		string str = readDigits(4,num/10000,flag,false);
		cout << str << " Wan";
		num %= 10000;
		flag = true;
	}
	string str = readDigits(4,num,flag,false);
	if(!flag && str==""){
		cout << digit[0];
	}
	else{
		cout << str;
	}

	system("pause");
	return 0;
}