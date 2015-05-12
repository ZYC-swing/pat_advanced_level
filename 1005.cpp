//1005.Spell It Right
/*
Given a non-negative integer N, your task is to compute the sum of all the digits of N, and output every digit of the sum in English.

Input Specification:

Each input file contains one test case. Each case occupies one line which contains an N (<= 10100).

Output Specification:

For each test case, output in one line the digits of the sum in English words. There must be one space between two consecutive words, but no extra space at the end of a line.

Sample Input:
12345
Sample Output:
one five
*/
#include <iostream>
#include <string>
using namespace std;

string number[10]={"zero","one","two","three","four","five","six","seven","eight","nine"};

void spell(int num){
	if(num/10>0){
		spell(num/10);
		cout << " ";
	}
	cout << number[num%10];
}

int main(){
	string str;
	int sum=0;

	cin >> str;
	for(int i=0; i<str.length(); i++){
		sum = sum+str[i]-'0';
	}
	spell(sum);

	system("pause");
	return 0;
}

//第二遍刷
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

const vector<string> digits{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main(){
	string num;
	stack<string> st;
	int sum = 0;

	cin >> num;
	for (auto i : num){
		sum += i - '0';
	}
	do{
		st.push(digits[sum % 10]);
		sum /= 10;
	} while (sum);
	while (!st.empty()){
		cout << st.top();
		st.pop();
		if (!st.empty()){
			cout << " ";
		}
	}
	system("pause");
	return 0;
}