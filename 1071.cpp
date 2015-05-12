//1071. Speech Patterns
/*
People often have a preference among synonyms of the same word. For example, some may prefer "the police", while others may prefer "the cops". Analyzing such patterns can help to narrow down a speaker's identity, which is useful when validating, for example, whether it's still the same person behind an online avatar.

Now given a paragraph of text sampled from someone's speech, can you find the person's most commonly used word?

Input Specification:

Each input file contains one test case. For each case, there is one line of text no more than 1048576 characters in length, terminated by a carriage return '\n'. The input contains at least one alphanumerical character, i.e., one character from the set [0-9 A-Z a-z].

Output Specification:

For each test case, print in one line the most commonly occurring word in the input text, followed by a space and the number of times it has occurred in the input. If there are more than one such words, print the lexicographically smallest one. The word should be printed in all lower case. Here a "word" is defined as a continuous sequence of alphanumerical characters separated by non-alphanumerical characters or the line beginning/end.

Note that words are case insensitive.

Sample Input:
Can1: "Can a can can a can?  It can!"
Sample Output:
can 5
*/
#include <iostream>
#include <string>
#include <map>
using namespace std;

bool isCharacter(char ch){
	return (ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z');
}

int main(int argc, char const *argv[])
{
	map<string,int> strs;
	string rawStr;

	getline(cin,rawStr);

	string str;
	int left,right;
	left = right = 0;
	for(int i=0; i<rawStr.length(); i++){
		if(isCharacter(rawStr[i])){
			if(rawStr[i]>='A' && rawStr[i]<='Z'){
				rawStr[i] -= 'A'-'a';
			}
			right++;
		}
		else{
			if(left<right){
				str.assign(rawStr,left,right-left);
				strs[str]++;
			}
			left = right = i+1;
		}
	}

	if(left<right){
		str.assign(rawStr,left,right-left);
		strs[str]++;
	}

	int maxCnt = 0;
	for(map<string,int>::iterator it=strs.begin(); it!=strs.end(); it++){
		if((*it).second>maxCnt){
			maxCnt = (*it).second;
			str = (*it).first;
		}
	}

	cout << str << " " << maxCnt;

	system("pause");
	return 0;
}