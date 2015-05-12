//1016. Phone Bills
/*
A long-distance telephone company charges its customers by the following rules:

Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called (at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone call records.

Input Specification:

Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and so on for each hour in the day.

The next line contains a positive number N (<= 1000), followed by N lines of records. Each phone call record consists of the name of the customer (string of up to 20 characters without space), the time and date (mm:dd:hh:mm), and the word "on-line" or "off-line".

For each test case, all dates will be within a single month. Each "on-line" record is paired with the chronologically next record for the same customer provided it is an "off-line" record. Any "on-line" records that are not paired with an "off-line" record are ignored, as are "off-line" records not paired with an "on-line" record. It is guaranteed that at least one call is well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using a 24-hour clock.

Output Specification:

For each test case, you must print a phone bill for each customer.

Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning and ending time and date (dd:hh:mm), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological order. Finally, print the total charge for the month in the format shown by the sample.

Sample Input:
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
10
CYLL 01:01:06:01 on-line
CYLL 01:28:16:05 off-line
CYJJ 01:01:07:00 off-line
CYLL 01:01:08:03 off-line
CYJJ 01:01:05:59 on-line
aaa 01:01:01:03 on-line
aaa 01:02:00:01 on-line
CYLL 01:28:15:41 on-line
aaa 01:05:02:24 on-line
aaa 01:04:23:59 off-line
Sample Output:
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int rate[24];

typedef struct{
	string name;
	string t;
	int tag;// 0 for on-line, 1 for off-line
	int d;
	int h;
	int m;
}record;

bool earlier(record a, record b){
	if (a.d<b.d || (a.d==b.d && a.h<b.h) || (a.d==b.d && a.h==b.h && a.m<b.m))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cmp(record a, record b){
	if (a.name<b.name)
	{
		return 1;
	}
	else if (a.name==b.name && earlier(a,b))
	{
		return 1;
	}
	else
		return 0;
}

float cal(record r1, record r2){
	float sum=0.0;
	float daycost=0.0;

	for(int i=0; i<24; i++){
		daycost += rate[i]*60;
	}
	sum += (r2.d-r1.d)*daycost;
	
	if(r1.h<=r2.h){
		sum = sum+(60-r1.m)*rate[r1.h]+(r2.m)*rate[r2.h];
		for(int i=r1.h+1; i<r2.h; i++){
			sum += rate[i]*60;
		}
	}
	else{
		sum = sum-(60-r2.m)*rate[r2.h]-(r1.m)*rate[r1.h];
		for(int i=r2.h+1; i<r1.h; i++){
			sum -= rate[i]*60;
		}
	}

	sum /= 100;
	return sum;
}

int main(int argc, char const *argv[])
{
	int n;
	vector<record> records;
	record tmp;
	string month;

	for (int i = 0; i < 24; ++i)
	{
		cin >> rate[i];
	}
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string name;
		string t;
		string tag;
		cin >> name >> t >> tag;
		tmp.name = name;
		tmp.t = t;
		if(tag == "on-line")
			tmp.tag = 0;
		else
			tmp.tag = 1;
		tmp.d = (tmp.t[3]-'0')*10+tmp.t[4]-'0';
		tmp.h = (tmp.t[6]-'0')*10+tmp.t[7]-'0';
		tmp.m = (tmp.t[9]-'0')*10+tmp.t[10]-'0';
		records.push_back(tmp);
	}

	sort(records.begin(), records.end(), cmp);
	month.assign((*records.begin()).t,0,2);
	string currentName="";
	int tag;
	float total;
	bool first;
	for (vector<record>::iterator it = records.begin(); it != records.end();)
	{
		string currentTime;
		record tmpRecord;
		if ((*it).name!=currentName)
		{
			tag = 0;
			total = 0.0;
			first = true;
			currentName = (*it).name;
			//cout << (*it).name << " ";
			//cout << ((*it).t)[0] << ((*it).t)[1] << endl;
			while((*it).tag!=tag && (*it).name==currentName){
				it++;
			}
		}
		while(it != records.end() && (*it).name==currentName){
			if((*it).tag==tag){
				if(tag==0){
					tmpRecord = *it;
					tag = 1;
				}
				else{
					if(first){
						cout << (*it).name << " " << month << endl;
						first = false;
					}
					printf("%02d:%02d:%02d ", tmpRecord.d, tmpRecord.h, tmpRecord.m);
					printf("%02d:%02d:%02d ", (*it).d, (*it).h, (*it).m);
					cout << (((*it).d-tmpRecord.d)*24+(*it).h-tmpRecord.h)*60+(*it).m-tmpRecord.m << " ";
					float cost = cal(tmpRecord, *it);
					total += cost;
					printf("$%.2f\n", cost);
					tag = 0;
				}
			}
			else if(tag==1){
				tmpRecord = *it;
			}
			it++;
		}
		if(!first)
			printf("Total amount: $%.2f\n", total);
	}

	system("pause");
	return 0;
}

//第二次刷
//这题写起来真麻烦啊。。。><
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cstdint>
#include <cmath>
using namespace std;

vector<int> toll(24);
int dayCost = 0;

struct MyTime{
	int month;
	int date;
	int hour;
	int minute;
	int cnt;
};

struct Record{
	char name[21];
	MyTime tt;
	bool on_line;
};

bool cmp(Record r1, Record r2){
	return strcmp(r1.name, r2.name) < 0 || (strcmp(r1.name, r2.name) == 0 && r1.tt.cnt < r2.tt.cnt);
}

int calOneDate(MyTime t){
	int res = 0;
	for (int i = 0; i < t.hour; ++i){
		res += toll[i] * 60;
	}
	res += toll[t.hour] * t.minute;
	return res;
}

int cal(MyTime start, MyTime end){
	int res;
	if (start.date < end.date){
		res = (end.date - start.date)*dayCost;
		start.cnt += (end.date - start.date) * 24 * 60;
		start.date = end.date;
		return res + cal(start, end);
	}
	if (start.cnt > end.cnt){
		return -cal(end, start);
	}
	return calOneDate(end) - calOneDate(start);
}

int main(){
	for (int i = 0; i < 24; ++i){
		cin >> toll[i];
		dayCost += toll[i] * 60;
	}
	int n;
	cin >> n;
	vector<Record> records(n);
	for (int i = 0; i < n; ++i){
		char mark[10];
		scanf("%s %d:%d:%d:%d %s", records[i].name, &records[i].tt.month, &records[i].tt.date, &records[i].tt.hour, &records[i].tt.minute, mark);
		records[i].on_line = mark[1] == 'n';
		records[i].tt.cnt = records[i].tt.date * 24 * 60 + records[i].tt.hour * 60 + records[i].tt.minute;
	}
	sort(records.begin(), records.end(), cmp);
	char tmpName[21] = "";
	bool wait_on_line = 1;
	vector<pair<MyTime, MyTime>> validRecords;
	MyTime start;
	for (int i = 0; i < n; ++i){
		if (strcmp(records[i].name, tmpName) != 0){
			if (strcmp(records[i].name, "") != 0){
				if (validRecords.size()){
					printf("%s %02d\n", tmpName, validRecords[0].first.month);
					float sum = 0;
					for (auto j : validRecords){
						sum += cal(j.first, j.second) * 1.0 / 100;
						printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", j.first.date, j.first.hour, j.first.minute, j.second.date, j.second.hour, j.second.minute, \
							j.second.cnt - j.first.cnt, cal(j.first, j.second) * 1.0 / 100);
					}
					printf("Total amount: $%.2f\n", sum);
				}
				validRecords.clear();
			}
			strcpy(tmpName, records[i].name);
			wait_on_line = 1;
		}
		if (wait_on_line){
			if (!records[i].on_line){
				continue;
			}
			start = records[i].tt;
			wait_on_line = 0;
		}
		else{
			if (records[i].on_line){
				start = records[i].tt;
			}
			else{
				validRecords.push_back(make_pair(start, records[i].tt));
				wait_on_line = 1;
			}
		}
	}
	if (validRecords.size()){
		printf("%s %02d\n", tmpName, validRecords[0].first.month);
		float sum = 0;
		for (auto j : validRecords){
			sum += cal(j.first, j.second) * 1.0 / 100;
			printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", j.first.date, j.first.hour, j.first.minute, j.second.date, j.second.hour, j.second.minute, \
				j.second.cnt - j.first.cnt, cal(j.first, j.second) * 1.0 / 100);
		}
		printf("Total amount: $%.2f\n", sum);
	}

	system("pause");
	return 0;
}