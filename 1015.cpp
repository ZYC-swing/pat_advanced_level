//1015. Reversible Primes
/*
A reversible prime in any number system is a prime whose "reverse" in that number system is also a prime. For example in the decimal system 73 is a reversible prime because its reverse 37 is also a prime.

Now given any two positive integers N (< 105) and D (1 < D <= 10), you are supposed to tell if N is a reversible prime with radix D.

Input Specification:

The input file consists of several test cases. Each case occupies a line which contains two integers N and D. The input is finished by a negative N.

Output Specification:

For each test case, print in one line "Yes" if N is a reversible prime with radix D, or "No" if not.

Sample Input:
73 10
23 2
23 10
-2
Sample Output:
Yes
Yes
No
*/
#include <iostream>
#include <cmath>
using namespace std;

int reverseNumber(int n, int d){
	int ret = 0;

	while(n){
		ret = ret*d+n%d;
		n /= d;
	}

	return ret;
}

bool isPrime(int n){
	if(n<2)
		return 0;
	for(int i=2; i<=sqrt((float)n); i++){
		if (n%i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char const *argv[])
{
	int n,d,rev;

	cin >> n;
	while(n>=0){
		cin >> d;
		rev = reverseNumber(n,d);
		if(isPrime(n) && isPrime(rev))
			cout << "Yes";
		else
			cout << "No";
		cout << endl;
		cin >> n;
	}

	system("pause");
	return 0;
}

//第二次刷代码几乎一样就不贴了