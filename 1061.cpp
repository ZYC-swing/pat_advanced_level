//1061. Dating
/*
Sherlock Holmes received a note with some strange strings: "Let's date! 3485djDkxh4hhGE 2984akDfkkkkggEdsb s&hgsfdk d&Hyscvnm". It took him only a minute to figure out that those strange strings are actually referring to the coded time "Thursday 14:04" -- since the first common capital English letter (case sensitive) shared by the first two strings is the 4th capital letter 'D', representing the 4th day in a week; the second common character is the 5th capital letter 'E', representing the 14th hour (hence the hours from 0 to 23 in a day are represented by the numbers from 0 to 9 and the capital letters from A to N, respectively); and the English letter shared by the last two strings is 's' at the 4th position, representing the 4th minute. Now given two pairs of strings, you are supposed to help Sherlock decode the dating time.

Input Specification:

Each input file contains one test case. Each case gives 4 non-empty strings of no more than 60 characters without white space in 4 lines.

Output Specification:

For each test case, print the decoded time in one line, in the format "DAY HH:MM", where "DAY" is a 3-character abbreviation for the days in a week -- that is, "MON" for Monday, "TUE" for Tuesday, "WED" for Wednesday, "THU" for Thursday, "FRI" for Friday, "SAT" for Saturday, and "SUN" for Sunday. It is guaranteed that the result is unique for each case.

Sample Input:
3485djDkxh4hhGE 
2984akDfkkkkggEdsb 
s&hgsfdk 
d&Hyscvnm
Sample Output:
THU 14:04
*/
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

const string day[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};

int main(int argc, char const *argv[])
{
	string str[4];

	for(int i=0; i<4; i++){
		cin >> str[i];
	}

	bool first = true;
	for(int index=0; index<str[0].length() && index<str[1].length(); index++){
		if(first && str[0][index]==str[1][index] && str[0][index]>='A' && str[0][index]<='G'){
			first = false;
			cout << day[str[0][index]-'A'] << " ";
		}
		else if(!first && str[0][index]==str[1][index]){
			if(str[0][index]>='0' && str[0][index]<='9'){
				cout << "0" << str[0][index] << ":";
				break;
			}
			else if(str[0][index]>='A' && str[0][index]<='N'){
				cout << str[0][index]-'A'+10 << ":";
				break;
			}
		}
	}

	for(int index=0; index<str[2].length() && index<str[3].length(); index++){
		if(str[2][index]==str[3][index] && ((str[2][index]>='a' && str[2][index]<='z') || (str[2][index]>='A' && str[2][index]<='Z'))){
			printf("%02d", index);
		}
	}

	system("pause");
	return 0;
}