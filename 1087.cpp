//1087. All Roads Lead to Rome
/*
Indeed there are many different tourist routes from our city to Rome. You are supposed to find your clients the route with the least cost while gaining the most happiness.

Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive integers N (2<=N<=200), the number of cities, and K, the total number of routes between pairs of cities; followed by the name of the starting city. The next N-1 lines each gives the name of a city and an integer that represents the happiness one can gain from that city, except the starting city. Then K lines follow, each describes a route between two cities in the format "City1 City2 Cost". Here the name of a city is a string of 3 capital English letters, and the destination is always ROM which represents Rome.

Output Specification:

For each test case, we are supposed to find the route with the least cost. If such a route is not unique, the one with the maximum happiness will be recommended. If such a route is still not unique, then we output the one with the maximum average happiness -- it is guaranteed by the judge that such a solution exists and is unique.

Hence in the first line of output, you must print 4 numbers: the number of different routes with the least cost, the cost, the happiness, and the average happiness (take the integer part only) of the recommended route. Then in the next line, you are supposed to print the route in the format "City1->City2->...->ROM".

Sample Input:
6 7 HZH
ROM 100
PKN 40
GDN 55
PRS 95
BLN 80
ROM GDN 1
BLN ROM 1
HZH PKN 1
PRS ROM 2
BLN HZH 2
PKN GDN 1
HZH PRS 1
Sample Output:
3 3 195 97
HZH->PRS->ROM
*/
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <stack>
using namespace std;

#define INF 0x0fffffff

map<string,int> name2id;
map<int,string> id2name;
vector<int> happiness,dist;
vector<vector<int>> weight;
stack<int> path;
int n,k,maxHappiness,cityCnt,pathCnt;

bool dfs(int index, int h, int cnt){
	h += happiness[index];
	cnt++;
	if(index==name2id["ROM"]){
		pathCnt++;
		if(h>maxHappiness || (h==maxHappiness && cnt<cityCnt)){
			maxHappiness = h;
			cityCnt = cnt;
			while(!path.empty()){
				path.pop();
			}
			path.push(index);
			return true;
		}
		return false;
	}
	else{
		bool flag = false;
		for(int i=0; i<n; i++){
			if(dist[index]+weight[index][i]==dist[i]){
				if(dfs(i,h,cnt)){
					path.push(index);
					flag = true;
				}
			}
		}
		return flag;
	}
}

int main(int argc, char const *argv[])
{
	cin >> n >> k;

	happiness.resize(n);
	dist.assign(n,INF);
	weight.resize(n);
	for(int i=0; i<n; i++){
		weight[i].assign(n,INF);
	}
	vector<bool> visited;
	visited.assign(n,0);

	string name;
	cin >> name;
	name2id[name] = 0;
	id2name[0] = name;
	happiness[0] = 0;
	for(int i=1; i<n; i++){
		int h;
		cin >> name >> h;
		name2id[name] = i;
		id2name[i] = name;
		happiness[i] = h;
	}

	for(int i=0; i<k; i++){
		string c[2];
		int cost,id[2];

		cin >> c[0] >> c[1] >> cost;
		for(int j=0; j<2; j++){
			id[j] = name2id[c[j]];
		}
		weight[id[0]][id[1]] = weight[id[1]][id[0]] = cost;
	}

	//Dijkstra
	visited[0] = 1;
	dist[0] = 0;
	int index = 0;
	for(int i=1; i<n; i++){
		int min = INF, nextIndex;
		for(int j=1; j<n; j++){
			if(!visited[j]){
				if(dist[index]+weight[index][j]<dist[j]){
					dist[j] = dist[index]+weight[index][j];
				}
				if(dist[j]<min){
					min = dist[j];
					nextIndex = j;
				}
			}
		}
		if(min==INF){
			break;
		}
		index = nextIndex;
		visited[index] =1;
	}

	maxHappiness = -INF;
	cityCnt = INF;
	pathCnt = 0;
	dfs(0,0,-1);
	
	cout << pathCnt << " " << dist[name2id["ROM"]] << " " << maxHappiness << " " << maxHappiness/cityCnt << endl;
	bool first = true;
	while(!path.empty()){
		if(first){
			first = false;
		}
		else{
			cout << "->";
		}
		cout << id2name[path.top()];
		path.pop();
	}

	system("pause");
	return 0;
}