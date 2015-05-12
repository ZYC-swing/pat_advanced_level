//1002.A+B for Polynomials
/*
This time, you are supposed to find A+B where A and B are two polynomials.

Input

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. It is given that 1 <= K <= 10，0 <= NK < ... < N2 < N1 <=1000.

Output

For each test case you should output the sum of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 2 1.5 1 2.9 0 3.2
*/

#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

#define threshold 0.05

int main(){
	float coeff[1001];
	int k,index;
	int nonZeroCnt;//记录非零系数个数
	float tmp;//系数

	for(int i=0;i<=1000;i++)
		coeff[i]=0.0;
	cin >> k;
	nonZeroCnt = k;
	while(k--){
		cin >> index >> tmp;
		coeff[index] = tmp;
	}
	cin >> k;
	while(k--){
		cin >> index >> tmp;
		if (fabs(coeff[index])<threshold)
		{
			coeff[index] += tmp;
			nonZeroCnt++;
		}
		else{
			coeff[index] += tmp;
			if (fabs(coeff[index])<threshold)
			{
				nonZeroCnt--;
			}
		}
	}
	cout << nonZeroCnt;
	for(int i=1000;i>=0;i--){
		if (fabs(coeff[i])>=threshold)
		{
			printf(" %d %.1f",i,coeff[i]);
		}
	}

	system("pause");
	return 0;
}