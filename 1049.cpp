//1049. Counting Ones
/*
The task is simple: given any positive integer N, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to N. For example, given N being 12, there are five 1's in 1, 10, 11, and 12.

Input Specification:

Each input file contains one test case which gives the positive N (<=230).

Output Specification:

For each test case, print the number of 1's in one line.

Sample Input:
12
Sample Output:
5
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	long long number,tmp,p;
	int cnt;

	cin >> number;
	p = 1;
	tmp = number;
	cnt = 0;
	while(tmp){
		cnt += (tmp/10)*p;
		if(tmp%10>1){
			cnt += p;
		}
		else if(tmp%10==1){
			cnt += (number%p+1);
		}
		tmp /= 10;
		p *= 10;
	}

	cout << cnt;
	
	system("pause");
	return 0;
}