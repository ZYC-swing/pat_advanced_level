//1081. Rational Sum
/*
Given N rational numbers in the form "numerator/denominator", you are supposed to calculate their sum.

Input Specification:

Each input file contains one test case. Each case starts with a positive integer N (<=100), followed in the next line N rational numbers "a1/b1 a2/b2 ..." where all the numerators and denominators are in the range of "long int". If there is a negative number, then the sign must appear in front of the numerator.

Output Specification:

For each test case, output the sum in the simplest form "integer numerator/denominator" where "integer" is the integer part of the sum, "numerator" < "denominator", and the numerator and the denominator have no common factor. You must output only the fractional part if the integer part is 0.

Sample Input 1:
5
2/5 4/15 1/30 -2/60 8/3
Sample Output 1:
3 1/3
Sample Input 2:
2
4/3 2/3
Sample Output 2:
2
Sample Input 3:
3
1/3 -1/6 1/8
Sample Output 3:
7/24
*/
#include <iostream>
#include <cstdio>
using namespace std;

#define MAXN 100

int gcd(int a, int b){
	if(a<=b){
		if(b%a==0){
			return a;
		}
		return gcd(a,b%a);
	}
	else{//a>b
		if(a%b==0){
			return b;
		}
		return gcd(a%b,b);
	}
}

int main(int argc, char const *argv[])
{
	int numerator,denominator,n;
	int preNumerator=0,preDenominator=1;
	int gongYueShu;
	
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d/%d", &numerator, &denominator);
		preNumerator = preNumerator*denominator+numerator*preDenominator;
		preDenominator *= denominator;
		if(preNumerator==0){
			preDenominator = 1;
			continue;
		}
		gongYueShu = gcd(preNumerator,preDenominator);
		preNumerator /= gongYueShu;
		preDenominator /= gongYueShu;
	}

	if(preNumerator==0){
		cout << 0;
	}
	else{
		if(preDenominator==1){
			cout << preNumerator;
		}
		else{
			int integer = preNumerator/preDenominator;
			if(integer!=0){
				cout << integer << " ";
			}
			cout << preNumerator%preDenominator << '/' << preDenominator;
		}
	}

	system("pause");
	return 0;
}