//1084. Broken Keyboard
/*
On a broken keyboard, some of the keys are worn out. So when you type some sentences, the characters corresponding to those keys will not appear on screen.

Now given a string that you are supposed to type, and the string that you actually type out, please list those keys which are for sure worn out.

Input Specification:

Each input file contains one test case. For each case, the 1st line contains the original string, and the 2nd line contains the typed-out string. Each string contains no more than 80 characters which are either English letters [A-Z] (case insensitive), digital numbers [0-9], or "_" (representing the space). It is guaranteed that both strings are non-empty.

Output Specification:

For each test case, print in one line the keys that are worn out, in the order of being detected. The English letters must be capitalized. Each worn out key must be printed once only. It is guaranteed that there is at least one worn out key.

Sample Input:
7_This_is_a_test
_hs_s_a_es
Sample Output:
7TI
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	string str[2];
	vector<char> broken;
	set<char> ss;

	cin >> str[0] >> str[1];
	for(int i=0; i<2; i++){
		transform(str[i].begin(),str[i].end(),str[i].begin(),::toupper);
	}
	for(int i=0; i<str[1].length(); i++){
		ss.insert(str[1][i]);
	}
	for(int i=0; i<str[0].length(); i++){
		if(ss.find(str[0][i])==ss.end()){
			ss.insert(str[0][i]);
			broken.push_back(str[0][i]);
		}
	}
	for(int i=0; i<broken.size(); i++){
		cout << broken[i];
	}
	
	system("pause");
	return 0;
}