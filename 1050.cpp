//1050. String Subtraction
/*
Given two strings S1 and S2, S = S1 - S2 is defined to be the remaining string after taking all the characters in S2 from S1. Your task is simply to calculate S1 - S2 for any given strings. However, it might not be that simple to do it fast.

Input Specification:

Each input file contains one test case. Each case consists of two lines which gives S1 and S2, respectively. The string lengths of both strings are no more than 104. It is guaranteed that all the characters are visible ASCII codes and white space, and a new line character signals the end of a string.

Output Specification:

For each test case, print S1 - S2 in one line.

Sample Input:
They are students.
aeiou
Sample Output:
Thy r stdnts.
*/
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	string str[2];
	set<char> chars;

	for(int i=0; i<2; i++){
		getline(cin,str[i]);
	}

	for(int i=0; i<str[1].length(); i++){
		if(chars.find(str[1][i])==chars.end()){
			chars.insert(str[1][i]);
		}
	}

	for(int i=0; i<str[0].length();){
		if(chars.find(str[0][i])==chars.end()){
			i++;
		}
		else{
			str[0].erase(str[0].begin()+i);
		}
	}

	cout << str[0];

	system("pause");
	return 0;
}