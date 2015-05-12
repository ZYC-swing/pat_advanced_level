//1059. Prime Factors
/*
Given any positive integer N, you are supposed to find all of its prime factors, and write them in the format N = p1^k1 * p2^k2 *…*pm^km.

Input Specification:

Each input file contains one test case which gives a positive integer N in the range of long int.

Output Specification:

Factor N in the format N = p1^k1 * p2^k2 *…*pm^km, where pi's are prime factors of N in increasing order, and the exponent ki is the number of pi -- hence when there is only one pi, ki is 1 and must NOT be printed out.

Sample Input:
97532468
Sample Output:
97532468=2^2*11*17*101*1291
*/
#include <iostream>
using namespace std;

bool isPrime(long long num){
	if(num<2){
		return false;
	}
	for(long long i=2; i<num/2+1; i++){
		if(num%i==0){
			return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[])
{
	long long num;
	bool first = true;

	cin >> num;
	cout << num << "=";

	if(num<2){
		cout << num;
		return 0;
	}
	for(long long i=2; i<=num; i++){
		if(isPrime(i)){
			int cnt=0;
			while(num%i==0){
				cnt++;
				num /= i;
			}
			if(cnt==0){
				continue;
			}
			if(first){
				first = false;
			}
			else{
				cout << '*';
			}
			if(cnt==1){
				cout << i;
			}
			else{
				cout << i << '^' << cnt;
			}
		}
	}
	system("pause");
	return 0;
}