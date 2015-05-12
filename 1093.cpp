//1093. Count PAT's
/*
The string APPAPT contains two PAT's as substrings. The first one is formed by the 2nd, the 4th, and the 6th characters, and the second one is formed by the 3rd, the 4th, and the 6th characters.

Now given any string, you are supposed to tell the number of PAT's contained in the string.

Input Specification:

Each input file contains one test case. For each case, there is only one line giving a string of no more than 105 characters containing only P, A, or T.

Output Specification:

For each test case, print in one line the number of PAT's contained in the string. Since the result may be a huge number, you only have to output the result moded by 1000000007.

Sample Input:
APPAPT
Sample Output:
2
*/
#include <iostream>
#include <string>
using namespace std;

#define SIZE 1000000007

int main(){
	string str;
	cin >> str;
	int pCnt, aCnt, total;
	pCnt = aCnt = total = 0;
	for (int i = 0; i < str.length(); ++i){
		switch (str[i]){
		case 'P':
			++pCnt;
			pCnt %= SIZE;
			break;
		case 'A':
			aCnt += pCnt;
			aCnt %= SIZE;
			break;
		default:
			total += aCnt;
			total %= SIZE;
			break;
		}
	}
	cout << total;

	system("pause");
	return 0;
}