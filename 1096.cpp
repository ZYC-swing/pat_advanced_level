//1096. Consecutive Factors
/*
Among all the factors of a positive integer N, there may exist several consecutive numbers. For example, 630 can be factored as 3*5*6*7, where 5, 6, and 7 are the three consecutive numbers. Now given any positive N, you are supposed to find the maximum number of consecutive factors, and list the smallest sequence of the consecutive factors.

Input Specification:

Each input file contains one test case, which gives the integer N (1<N<231).

Output Specification:

For each test case, print in the first line the maximum number of consecutive factors. Then in the second line, print the smallest sequence of the consecutive factors in the format "factor[1]*factor[2]*...*factor[k]", where the factors are listed in increasing order, and 1 is NOT included.

Sample Input:
630
Sample Output:
3
5*6*7
*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int n;
	cin >> n;
	int maxCnt = 1, first = n;
	for (int i = 2; i <= sqrt(n) + 0.5; ++i){
		int cnt = 0, remain = n, j;
		for (j = i; remain % j == 0; remain /= j, ++j);
		if (j - i > maxCnt || (j - i == maxCnt && i < first)){
			maxCnt = j - i;
			first = i;
		}
	}
	cout << maxCnt << endl;
	cout << first;
	for (int i = 1; i < maxCnt; ++i){
		cout << '*' << first + i;
	}
	system("pause");
	return 0;
}