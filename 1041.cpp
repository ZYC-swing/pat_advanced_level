//1041. Be Unique
/*
Being unique is so important to people on Mars that even their lottery is designed in a unique way. The rule of winning is simple: one bets on a number chosen from [1, 104]. The first one who bets on a unique number wins. For example, if there are 7 people betting on 5 31 5 88 67 88 17, then the second one who bets on 31 wins.

Input Specification:

Each input file contains one test case. Each case contains a line which begins with a positive integer N (<=105) and then followed by N bets. The numbers are separated by a space.

Output Specification:

For each test case, print the winning number in a line. If there is no winner, print "None" instead.

Sample Input 1:
7 5 31 5 88 67 88 17
Sample Output 1:
31
Sample Input 2:
5 888 666 666 888 888
Sample Output 2:
None
*/
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	map<int,int> cnt;
	vector<int> input;
	map<int,int>::iterator it_map;
	vector<int>::iterator it_vec;
	int n,num;

	cin >> n;
	while(n--){
		cin >> num;
		input.push_back(num);
		it_map = cnt.find(num);
		if(it_map==cnt.end()){
			cnt[num] = 1;
		}
		else{
			cnt[num]++;
		}
	}

	for(it_vec=input.begin(); it_vec!=input.end(); it_vec++){
		if(cnt.find((*it_vec))!=cnt.end() && cnt[(*it_vec)]==1){
			cout << (*it_vec);
			break;
		}
	}

	if(it_vec==input.end())
		cout << "None";

	system("pause");
	return 0;
}