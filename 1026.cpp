//1026. Table Tennis
/*
A table tennis club has N tables available to the public. The tables are numbered from 1 to N. For any pair of players, if there are some tables open when they arrive, they will be assigned to the available table with the smallest number. If all the tables are occupied, they will have to wait in a queue. It is assumed that every pair of players can play for at most 2 hours.

Your job is to count for everyone in queue their waiting time, and for each table the number of players it has served for the day.

One thing that makes this procedure a bit complicated is that the club reserves some tables for their VIP members. When a VIP table is open, the first VIP pair in the queue will have the priviledge to take it. However, if there is no VIP in the queue, the next pair of players can take it. On the other hand, if when it is the turn of a VIP pair, yet no VIP table is available, they can be assigned as any ordinary players.

Input Specification:

Each input file contains one test case. For each case, the first line contains an integer N (<=10000) - the total number of pairs of players. Then N lines follow, each contains 2 times and a VIP tag: HH:MM:SS - the arriving time, P - the playing time in minutes of a pair of players, and tag - which is 1 if they hold a VIP card, or 0 if not. It is guaranteed that the arriving time is between 08:00:00 and 21:00:00 while the club is open. It is assumed that no two customers arrives at the same time. Following the players' info, there are 2 positive integers: K (<=100) - the number of tables, and M (< K) - the number of VIP tables. The last line contains M table numbers.

Output Specification:

For each test case, first print the arriving time, serving time and the waiting time for each pair of players in the format shown by the sample. Then print in a line the number of players served by each table. Notice that the output must be listed in chronological order of the serving time. The waiting time must be rounded up to an integer minute(s). If one cannot get a table before the closing time, their information must NOT be printed.

Sample Input:
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 1
2
Sample Output:
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_TABLE_NUM 100

typedef struct{
	int arriveTime[3];//hh:mm:ss
	int at;
	int servedTime[3];//hh:mm:ss
	int st;
	int playingTime;
	bool vip;
}player;

bool cmpArrive(player p1, player p2){
	return p1.at<p2.at;
}

bool cmpServe(player p1, player p2){
	return (p1.st<p2.st)||(p1.st==p2.st && p1.at<p2.at);
}

int main(int argc, char const *argv[])
{
	queue<player> tables[MAX_TABLE_NUM];
	queue<player> waitOrdinary,waitVip;
	vector<player> players;
	vector<player> servedPlayers;
	vector<int> vipTables;
	int n,k,m,served[MAX_TABLE_NUM];
	bool vipSignal[MAX_TABLE_NUM];

	memset(served,0,sizeof(served));
	memset(vipSignal,0,sizeof(vipSignal));
	
	cin >> n;
	for(int i=0; i<n; i++){
		player tmp;
		scanf("%d:%d:%d %d %d", &tmp.arriveTime[0]
			, &tmp.arriveTime[1], &tmp.arriveTime[2]
			, &tmp.playingTime, &tmp.vip);
		tmp.at = tmp.arriveTime[0]*3600+tmp.arriveTime[1]*60+tmp.arriveTime[2];
		if(tmp.arriveTime[0]>=21){
			continue;
		}
		if(tmp.playingTime>120){
			tmp.playingTime = 120;
		}
		tmp.playingTime *= 60;
		players.push_back(tmp);
	}
	cin >> k >> m;
	int index;
	for(int i=0; i<m; i++){
		cin >> index;
		vipSignal[index-1] = 1;
		vipTables.push_back(index-1);
	}
	sort(vipTables.begin(),vipTables.end());

	sort(players.begin(), players.end(), cmpArrive);
	for(vector<player>::iterator it = players.begin(); it != players.end(); ++it){
		if((*it).vip){
			waitVip.push(*it);
		}
		else{
			waitOrdinary.push(*it);
		}
	}
	players.clear();
	
	int startTime = 8*3600;
	int endTime = 21*3600;
	int currentTime = startTime;
	while(currentTime<endTime){
		int passTime = endTime-currentTime;

		//先把所有等待的VIP分配到可分配的VIP桌上
		while(!waitVip.empty() && waitVip.front().at<=currentTime){
			vector<int>::iterator it;
			for(it=vipTables.begin(); it!=vipTables.end(); it++){
				if(tables[*it].empty()){
					waitVip.front().st = currentTime;
					tables[*it].push(waitVip.front());
					served[*it]++;
					waitVip.pop();
					if(tables[*it].front().playingTime<passTime){
						passTime = tables[*it].front().playingTime;
					}
					break;
				}
			}
			if(it==vipTables.end()){
				break;
			}
		}

		for(int index=0; index<k; index++){
			if(!tables[index].empty()){
				if(tables[index].front().playingTime<passTime){
					passTime = tables[index].front().playingTime;
				}
			}
			else{
				//普通球员和VIP球员都没有在等待的
				if(!(!waitOrdinary.empty() && waitOrdinary.front().at<=currentTime) && !(!waitVip.empty() && waitVip.front().at<=currentTime)){
					if(!waitOrdinary.empty() && waitOrdinary.front().at-currentTime<passTime){
						passTime = waitOrdinary.front().at-currentTime;
					}
					if(!waitVip.empty() && waitVip.front().at-currentTime<passTime){
						passTime = waitVip.front().at-currentTime;
					}
				}
				//只有普通球员在等待
				else if(!waitOrdinary.empty() && waitOrdinary.front().at<=currentTime && !(!waitVip.empty() && waitVip.front().at<=currentTime)){
					waitOrdinary.front().st = currentTime;
					tables[index].push(waitOrdinary.front());
					served[index]++;
					waitOrdinary.pop();
					if(tables[index].front().playingTime<passTime){
						passTime = tables[index].front().playingTime;
					}
				}
				//只有VIP球员在等待
				else if(!(!waitOrdinary.empty() && waitOrdinary.front().at<=currentTime) && !waitVip.empty() && waitVip.front().at<=currentTime){
					waitVip.front().st = currentTime;
					tables[index].push(waitVip.front());
					served[index]++;
					waitVip.pop();
					if(tables[index].front().playingTime<passTime){
						passTime = tables[index].front().playingTime;
					}
				}
				else{//普通球员和VIP球员都在等
					//VIP桌子不够分，公平竞争
					if(waitOrdinary.front().at<waitVip.front().at){
						waitOrdinary.front().st = currentTime;
						tables[index].push(waitOrdinary.front());
						waitOrdinary.pop();
					}
					else{
						waitVip.front().st = currentTime;
						tables[index].push(waitVip.front());
						waitVip.pop();
					}
					served[index]++;
					if(tables[index].front().playingTime<passTime){
						passTime = tables[index].front().playingTime;
					}
				}
			}
		}//for(int index=0; index<k; index++)

		currentTime += passTime;
		for(int index=0; index<k; index++){
			if(!tables[index].empty()){
				tables[index].front().playingTime -= passTime;
				if(tables[index].front().playingTime==0){
					servedPlayers.push_back(tables[index].front());
					tables[index].pop();
				}
			}
		}
	}
	for(int index=0; index<k; index++){
		if(!tables[index].empty()){
			servedPlayers.push_back(tables[index].front());
			tables[index].pop();
		}
	}

	sort(servedPlayers.begin(),servedPlayers.end(),cmpServe);
	for(vector<player>::iterator it=servedPlayers.begin(); it!=servedPlayers.end(); it++){
		(*it).servedTime[0] = (*it).st/3600;
		(*it).servedTime[1] = ((*it).st%3600)/60;
		(*it).servedTime[2] = (*it).st%60;
		printf("%02d:%02d:%02d ", (*it).arriveTime[0], (*it).arriveTime[1], (*it).arriveTime[2]);
		printf("%02d:%02d:%02d ", (*it).servedTime[0], (*it).servedTime[1], (*it).servedTime[2]);
		cout << ((*it).st-(*it).at+30)/60 << endl;
	}
	for(int i=0; i<k; i++){
		cout << served[i];
		if(i!=k-1){
			cout << " ";
		}
	}

	system("pause");
	return 0;
}