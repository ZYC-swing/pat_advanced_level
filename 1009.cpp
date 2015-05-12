//1009.Product of Polynomials
/*
This time, you are supposed to find A*B where A and B are two polynomials.

Input Specification:

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. It is given that 1 <= K <= 10, 0 <= NK < ... < N2 < N1 <=1000.

Output Specification:

For each test case you should output the product of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate up to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 3 3.6 2 6.0 1 1.6
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
using namespace std;

#define ZERO 0.05

int main(){
	float coeff[2][1001],coeff_res[2001];
	int k,n;

	memset(coeff,0,sizeof(coeff));
	memset(coeff_res,0,sizeof(coeff_res));

	for(int i=0; i<2; i++){
		cin >> k;
		while(k--){
			cin >> n;
			cin >> coeff[i][n];
		}
	}

	int nonZeroCnt=0;
	for(int i=0; i<=2000;i++){
		int j;
		j = (i<=1000)?0:i-1000;
		for(; j<=i && j<=1000; j++){
			coeff_res[i] += coeff[0][j]*coeff[1][i-j];
		}
		if(fabs(coeff_res[i])>=ZERO)
			nonZeroCnt++;
	}

	cout << nonZeroCnt;
	for(int i=2000; i>=0; i--){
		if(fabs(coeff_res[i])>=ZERO)
			printf(" %d %.1f", i, coeff_res[i]);
	}

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main(){
	vector<vector<float>> vec(2, vector<float>(1001, 0.0));
	vector<float> res(2001, 0.0);
	int k, exp;
	float tmp;
	for (int i = 0; i < 2; ++i){
		cin >> k;
		while (k--){
			cin >> exp >> tmp;
			vec[i][exp] = tmp;
		}
	}
	for (int i = 0; i <= 1000; ++i){
		for (int j = 0; j <= 1000; ++j){
			res[i + j] += vec[0][i] * vec[1][j];
		}
	}
	stringstream ss;
	int cnt = 0;
	for (int i = 2000; i >= 0; --i){
		if (fabs(res[i]) >= 0.5){
			ss << " " << i << " " << fixed << setprecision(1) << res[i];
			++cnt;
		}
	}
	cout << cnt << ss.str();
	system("pause");
	return 0;
}