//1023. Have Fun with Numbers
/*
Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it again!

Now you are suppose to check if there are more numbers with this property. That is, double a given number with k digits, you are to tell if the resulting number consists of only a permutation of the digits in the original number.

Input Specification:

Each input file contains one test case. Each case contains one positive integer with no more than 20 digits.

Output Specification:

For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the doubled number.

Sample Input:
1234567899
Sample Output:
Yes
2469135798
*/
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
using namespace std;

int main(int argc, char const *argv[])
{
	string str;
	stack<int> num;
	int cnt[2][10];

	memset(cnt,0,sizeof(cnt));
	cin >> str;

	//删掉前面多余的0，发现其实没有设这个陷阱= =
	for(string::iterator it=str.begin(); it!=str.end();){
		if(*it!='0'){
			break;
		}
		else{
			str.erase(it);
		}
	}
	
	for(int i=0; i<str.length(); i++){
		cnt[0][str[i]-'0']++;
	}
	int up=0;
	int tmp;
	for(int i=str.length()-1; i>=0; i--){
		tmp = (str[i]-'0')*2+up;
		cnt[1][tmp%10]++;
		num.push(tmp%10);
		up = tmp/10;
	}
	if(up){
		cout << "No" << endl;
		cout << up;
	}
	else{
		int i;
		for(i=0; i<10; i++){
			if(cnt[0][i]!=cnt[1][i]){
				break;
			}
		}
		if(i==10){
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	while(!num.empty()){
		cout << num.top();
		num.pop();
	}

	system("pause");
	return 0;
}