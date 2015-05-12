//1077. Kuchiguse
/*
The Japanese language is notorious for its sentence ending particles. Personal preference of such particles can be considered as a reflection of the speaker's personality. Such a preference is called "Kuchiguse" and is often exaggerated artistically in Anime and Manga. For example, the artificial sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:

Itai nyan~ (It hurts, nyan~)
Ninjin wa iyada nyan~ (I hate carrots, nyan~)
Now given a few lines spoken by the same character, can you find her Kuchiguse?

Input Specification:

Each input file contains one test case. For each case, the first line is an integer N (2<=N<=100). Following are N file lines of 0~256 (inclusive) characters in length, each representing a character's spoken line. The spoken lines are case sensitive.

Output Specification:

For each test case, print in one line the kuchiguse of the character, i.e., the longest common suffix of all N lines. If there is no such suffix, write "nai".

Sample Input 1:
3
Itai nyan~
Ninjin wa iyadanyan~
uhhh nyan~
Sample Output 1:
nyan~
Sample Input 2:
3
Itai!
Ninjinnwaiyada T_T
T_T
Sample Output 2:
nai
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	int n,index,minLen;
	vector<string> strs;

	cin >> n;
	getchar();
	strs.resize(n);
	minLen = 256;
	for(int i=0; i<n; i++){
		getline(cin,strs[i]);
		if(strs[i].length()<minLen){
			minLen = strs[i].length();
		}
	}
	for(index=0; index<minLen; index++){
		bool flag = true;
		char ch = strs[0][strs[0].size()-1-index];
		for(int i=1; i<n; i++){
			if(strs[i][strs[i].size()-1-index]!=ch){
				flag = false;
				break;
			}
		}
		if(!flag){
			break;
		}
	}

	string res;
	res.assign(strs[0].end()-index,strs[0].end());
	if(res.length()==0){
		cout << "nai";
	}
	else{
		cout << res;
	}

	system("pause");
	return 0;
}