//1095. Cars on Campus
/*
Zhejiang University has 6 campuses and a lot of gates. From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate. Now with all the information available, you are supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.

Input Specification:

Each input file contains one test case. Each case starts with two positive integers N (<= 10000), the number of records, and K (<= 80000) the number of queries. Then N lines follow, each gives a record in the format

plate_number hh:mm:ss status

where plate_number is a string of 7 English capital letters or 1-digit numbers; hh:mm:ss represents the time point in a day by hour:minute:second, with the earliest time being 00:00:00 and the latest 23:59:59; and status is either in or out.

Note that all times will be within a single day. Each "in" record is paired with the chronologically next record for the same car provided it is an "out" record. Any "in" records that are not paired with an "out" record are ignored, as are "out" records not paired with an "in" record. It is guaranteed that at least one car is well paired in the input, and no car is both "in" and "out" at the same moment. Times are recorded using a 24-hour clock.

Then K lines of queries follow, each gives a time point in the format hh:mm:ss. Note: the queries are given in ascending order of the times.

Output Specification:

For each query, output in a line the total number of cars parking on campus. The last line of output is supposed to give the plate number of the car that has parked for the longest time period, and the corresponding time length. If such a car is not unique, then output all of their plate numbers in a line in alphabetical order, separated by a space.

Sample Input:
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
Sample Output:
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct record{
	string pNumber;
	int tt;
	bool in;
};

bool cmpNumber(record r1, record r2){
	return r1.pNumber < r2.pNumber || (r1.pNumber == r2.pNumber && r1.tt < r2.tt);
}

bool cmpTime(record r1, record r2){
	return r1.tt < r2.tt;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<record> records(n);
	for (int i = 0; i < n; ++i){
		int hh, mm, ss;
		string tmp;
		cin >> records[i].pNumber;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		cin >> tmp;
		records[i].tt = (hh * 60 + mm) * 60 + ss;
		records[i].in = tmp[0] == 'i';
	}
	sort(records.begin(), records.end(), cmpNumber);
	vector<record> validRecords;
	vector<string> resNumbers;
	int total = -1, longest = 0, last_in;
	string tmp;
	bool first = 1, in = 1;
	for (int i = 0; i < n; ++i){
		if (first || tmp != records[i].pNumber){
			first = 0;
			if (!in){
				validRecords.pop_back();
			}
			if (total > longest){
				resNumbers.clear();
				resNumbers.push_back(tmp);
				longest = total;
			}
			else if (total == longest){
				resNumbers.push_back(tmp);
			}
			tmp = records[i].pNumber;
			in = 1;
			total = 0;
		}
		if (in){
			if (records[i].in){
				validRecords.push_back(records[i]);
				in = 0;
				last_in = records[i].tt;
			}
		}
		else{
			if (records[i].in){
				validRecords.pop_back();
				validRecords.push_back(records[i]);
				last_in = records[i].tt;
			}
			else{
				validRecords.push_back(records[i]);
				total += records[i].tt - last_in;
				in = 1;
			}
		}
	}
	if (!in){
		validRecords.pop_back();
	}
	if (total > longest){
		resNumbers.clear();
		resNumbers.push_back(tmp);
		longest = total;
	}
	else if (total == longest){
		resNumbers.push_back(tmp);
	}

	sort(validRecords.begin(), validRecords.end(), cmpTime);
	int index = 0, cnt = 0;
	for (int i = 0; i < k; ++i){
		int hh, mm, ss, tt;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		tt = (hh * 60 + mm) * 60 + ss;
		while (index < validRecords.size() && validRecords[index].tt <= tt){
			if (validRecords[index].in){
				++cnt;
			}
			else{
				--cnt;
			}
			++index;
		}
		cout << cnt << endl;
	}
	sort(resNumbers.begin(), resNumbers.end());
	for (auto i : resNumbers){
		cout << i << " ";
	}
	printf("%02d:%02d:%02d", longest / 3600, (longest / 60) % 60, longest % 60);

	system("pause");
	return 0;
}