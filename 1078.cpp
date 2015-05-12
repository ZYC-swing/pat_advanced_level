//1078. Hashing
/*
The task of this problem is simple: insert a sequence of distinct positive integers into a hash table, and output the positions of the input numbers. The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table. Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. If the maximum size given by the user is not prime, you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

Input Specification:

Each input file contains one test case. For each case, the first line contains two positive numbers: MSize (<=104) and N (<=MSize) which are the user-defined table size and the number of input numbers, respectively. Then N distinct positive integers are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line. All the numbers in a line are separated by a space, and there must be no extra space at the end of the line. In case it is impossible to insert the number, print "-" instead.

Sample Input:
4 4
10 6 4 15
Sample Output:
0 1 4 -
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<bool> mark;

bool isPrime(int n){
	if(n<2){
		return 0;
	}
	else{
		for(int i=2; i<=sqrt(n*1.0); i++){
			if(n%i==0){
				return false;
			}
		}
		return true;
	}
}

int minPrime(int n){
	while(!isPrime(n)){
		n++;
	}
	return n;
}

int findAndMark(int msize, int n){
	for(int i=0; i<msize; i++){
		if(!mark[(n+i*i)%msize]){
			mark[(n+i*i)%msize] = 1;
			return (n+i*i)%msize;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int msize,n;

	cin >> msize >> n;
	msize = minPrime(msize);
	mark.resize(msize);
	for(int i=0; i<n; i++){
		int num,p;
		cin >> num;
		p = findAndMark(msize,num);
		if(p>=0){
			cout << p;
		}
		else{
			cout << "-";
		}
		if(i<n-1){
			cout << " ";
		}
	}

	system("pause");
	return 0;
}