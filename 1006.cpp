//1006.Sign In and Sign Out
/*
At the beginning of every day, the first person who signs in the computer room will unlock the door, and the last one who signs out will lock the door. Given the records of signing in's and out's, you are supposed to find the ones who have unlocked and locked the door on that day.

Input Specification:

Each input file contains one test case. Each case contains the records for one day. The case starts with a positive integer M, which is the total number of records, followed by M lines, each in the format:

ID_number Sign_in_time Sign_out_time
where times are given in the format HH:MM:SS, and ID number is a string with no more than 15 characters.

Output Specification:

For each test case, output in one line the ID numbers of the persons who have unlocked and locked the door on that day. The two ID numbers must be separated by one space.

Note: It is guaranteed that the records are consistent. That is, the sign in time must be earlier than the sign out time for each person, and there are no two persons sign in or out at the same moment.

Sample Input:
3
CS301111 15:30:28 17:00:10
SC3021234 08:00:00 11:25:25
CS301133 21:45:00 21:58:40
Sample Output:
SC3021234 CS301133
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int main(){
	int m;
	string id;
	int time1,time2;
	vector<string> ids;
	int earliestIndex,latestIndex;
	int earliestTime,latestTime;
	earliestTime = 24*3600-1;
	latestTime = 0;

	cin >> m;
	for(int i=0; i<m; i++){
		cin >> id;
		int hh,mm,ss;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		time1 = hh*3600+mm*60+ss;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		time2 = hh*3600+mm*60+ss;
		
		ids.push_back(id);
		if(time1<earliestTime){
			earliestIndex = i;
			earliestTime = time1;
		}
		if(time2>latestTime){
			latestIndex = i;
			latestTime = time2;
		}
	}

	cout << ids.at(earliestIndex) << " " << ids.at(latestIndex);

	system("pause");
	return 0;
}

//第二遍刷
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main(){
	int m;
	pair<string, int> signIn, signOut;
	signIn.second = 24 * 3600 - 1;
	signOut.second = 0;
	cin >> m;
	while (m--){
		char id[15];
		int hh[2], mm[2], ss[2];
		scanf("%s %d:%d:%d %d:%d:%d", id, &hh[0], &mm[0], &ss[0], &hh[1], &mm[1], &ss[1]);
		int tmp0 = hh[0] * 3600 + mm[0] * 60 + ss[0];
		int tmp1 = hh[1] * 3600 + mm[1] * 60 + ss[1];
		if (tmp0 < signIn.second){
			signIn.first.assign(id);
			signIn.second = tmp0;
		}
		if (tmp1 > signOut.second){
			signOut.first.assign(id);
			signOut.second = tmp1;
		}
	}
	cout << signIn.first << " " << signOut.first;
	system("pause");
	return 0;
}