//1088. Rational Arithmetic
/*
For two rational numbers, your task is to implement the basic arithmetics, that is, to calculate their sum, difference, product and quotient.

Input Specification:

Each input file contains one test case, which gives in one line the two rational numbers in the format "a1/b1 a2/b2". The numerators and the denominators are all in the range of long int. If there is a negative sign, it must appear only in front of the numerator. The denominators are guaranteed to be non-zero numbers.

Output Specification:

For each test case, print in 4 lines the sum, difference, product and quotient of the two rational numbers, respectively. The format of each line is "number1 operator number2 = result". Notice that all the rational numbers must be in their simplest form "k a/b", where k is the integer part, and a/b is the simplest fraction part. If the number is negative, it must be included in a pair of parentheses. If the denominator in the division is zero, output "Inf" as the result. It is guaranteed that all the output integers are in the range of long int.

Sample Input 1:
2/3 -4/2
Sample Output 1:
2/3 + (-2) = (-1 1/3)
2/3 - (-2) = 2 2/3
2/3 * (-2) = (-1 1/3)
2/3 / (-2) = (-1/3)
Sample Input 2:
5/3 0/6
Sample Output 2:
1 2/3 + 0 = 1 2/3
1 2/3 - 0 = 1 2/3
1 2/3 * 0 = 0
1 2/3 / 0 = Inf
*/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <cmath>
using namespace std;

#define ll long long

ll gcd(ll a, ll b){
	if(a<b){
		return gcd(b,a);
	}
	else if(a%b==0){
		return b;
	}
	else{
		return gcd(b,a%b);
	}
}

string ll2str(ll num){
	string res = "";

	while(num){
		res.insert(res.begin(),num%10+'0');
		num /= 10;
	}

	return res;
}

string simplestForm(ll numerator, ll denominator){
	if(denominator==0){
		return "Inf";
	}
	else if(numerator==0){
		return "0";
	}
	else{
		string res = "";
		bool nf = false;

		if((numerator<0 && denominator>0) || (numerator>0 && denominator<0)){
			nf = true;
			res.append("(-");
		}
		numerator = abs(numerator);
		denominator = abs(denominator);

		ll tmp = gcd(numerator,denominator);
		numerator /= tmp;
		denominator /= tmp;
		if(numerator/denominator){
			ll tmp = numerator/denominator;
			numerator %= denominator;

			res.append(ll2str(tmp));

			if(numerator==0){
				if(nf){
					res.insert(res.end(),')');
				}
				return res;
			}
			else{
				res.append(" ");
			}
		}
		res.append(ll2str(numerator)+"/"+ll2str(denominator));
		if(nf){
			res.insert(res.end(),')');
		}

		return res;
	}
}

int main(int argc, char const *argv[])
{
	ll numerator[3],denominator[3];
	
	for(int i=0; i<2; i++){
		scanf("%lld/%lld", &numerator[i], &denominator[i]);
	}

	string newForm[3];
	for(int i=0; i<2; i++){
		newForm[i] = simplestForm(numerator[i], denominator[i]);
	}

	cout << newForm[0] << " + " << newForm[1] << " = ";
	numerator[2] = numerator[0]*denominator[1]+numerator[1]*denominator[0];
	denominator[2] = denominator[0]*denominator[1];
	newForm[2] = simplestForm(numerator[2], denominator[2]);
	cout << newForm[2] << endl;
	
	cout << newForm[0] << " - " << newForm[1] << " = ";
	numerator[2] = numerator[0]*denominator[1]-numerator[1]*denominator[0];
	denominator[2] = denominator[0]*denominator[1];
	newForm[2] = simplestForm(numerator[2], denominator[2]);
	cout << newForm[2] << endl;

	cout << newForm[0] << " * " << newForm[1] << " = ";
	numerator[2] = numerator[0]*numerator[1];
	denominator[2] = denominator[0]*denominator[1];
	newForm[2] = simplestForm(numerator[2], denominator[2]);
	cout << newForm[2] << endl;

	cout << newForm[0] << " / " << newForm[1] << " = ";
	numerator[2] = numerator[0]*denominator[1];
	denominator[2] = denominator[0]*numerator[1];
	newForm[2] = simplestForm(numerator[2], denominator[2]);
	cout << newForm[2];

	system("pause");
	return 0;
}