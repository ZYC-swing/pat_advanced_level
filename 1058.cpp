//1058. A+B in Hogwarts
/*
If you are a fan of Harry Potter, you would know the world of magic has its own currency system -- as Hagrid explained it to Harry, "Seventeen silver Sickles to a Galleon and twenty-nine Knuts to a Sickle, it's easy enough." Your job is to write a program to compute A+B where A and B are given in the standard form of "Galleon.Sickle.Knut" (Galleon is an integer in [0, 107], Sickle is an integer in [0, 17), and Knut is an integer in [0, 29)).

Input Specification:

Each input file contains one test case which occupies a line with A and B in the standard form, separated by one space.

Output Specification:

For each test case you should output the sum of A and B in one line, with the same format as the input.

Sample Input:
3.2.1 10.16.27
Sample Output:
14.1.28
*/
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char const *argv[])
{
	int Galleon[2],Sickle[2],Knut[2];

	for(int i=0; i<2; i++){
		scanf("%d.%d.%d", &Galleon[i], &Sickle[i], &Knut[i]);
	}
	
	Knut[0] += Knut[1];
	Sickle[0] = Sickle[0]+Sickle[1]+Knut[0]/29;
	Knut[0] %=29;
	Galleon[0] = Galleon[0]+Galleon[1]+Sickle[0]/17;
	Sickle[0] %=17;

	cout << Galleon[0] << '.' << Sickle[0] << '.' << Knut[0];
	system("pause");
	return 0;
}