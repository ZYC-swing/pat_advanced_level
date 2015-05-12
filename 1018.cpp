//1018. Public Bike Management
/*
There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world. One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. A station is said to be in perfect condition if it is exactly half-full. If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect. And more, all the stations on the way will be adjusted as well.

When a problem station is reported, PBMC will always choose the shortest path to reach that station. If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.


Figure 1
Figure 1 illustrates an example. The stations are represented by vertices and the roads correspond to the edges. The number on an edge is the time taken to reach one end station from another. The number written inside a vertex S is the current number of bikes stored at S. Given that the maximum capacity of each station is 10. To solve the problem at S3, we have 2 different shortest paths:

1. PBMC -> S1 -> S3. In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from S1 and then take 5 bikes to S3, so that both stations will be in perfect conditions.

2. PBMC -> S2 -> S3. This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one that will be chosen.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 numbers: Cmax (<= 100), always an even number, is the maximum capacity of each station; N (<= 500), the total number of stations; Sp, the index of the problem station (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and M, the number of roads. The second line contains N non-negative numbers Ci (i=1,...N) where each Ci is the current number of bikes at Si respectively. Then M lines follow, each contains 3 numbers: Si, Sj, and Tij which describe the time Tij taken to move betwen stations Si and Sj. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print your results in one line. First output the number of bikes that PBMC must send. Then after one space, output the path in the format: 0->S1->...->Sp. Finally after another space, output the number of bikes that we must take back to PBMC after the condition of Sp is adjusted to perfect.

Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC. The judge's data guarantee that such a path is unique.

Sample Input:
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
3 0->2->3 0

Sample Input:
10 3 3 5
3 4 10
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
1 0->2->3 5

Sample Input:
10 3 3 5
3 4 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
6 0->2->3 0

Sample Input:
10 7 4 9
4 9 9 0 8 8 4
0 1 1
0 4 5
0 7 1
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
6 7 1
Sample Output:
1 0->7->6->5->4 1

Sample Input:
10 5 5 7
6 3 6 4 10
0 1 1
0 4 2
0 5 4
1 2 1
2 3 1
3 5 1
4 5 2
Sample Output:
0 0->5 5

Sample Input:
10 5 5 7
6 3 6 4 10
0 1 1
0 4 2
0 5 5
1 2 1
2 3 1
3 5 1
4 5 2
Sample Output:
1 0->4->5 5
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

#define MAXIMUM 0x00ffffff

vector<int> stations,dist;
vector<bool> visited;
vector<vector<int>> weight;
stack<int> path;
int minSend = MAXIMUM,minReceive = MAXIMUM;
int cmax,n,sp,m;

bool dfs(int index, int remain, int maxSend){
	remain += stations[index]-cmax/2;
	if(remain<0){
		maxSend -= remain;
		remain = 0;
	}
	if(index==sp){
		if(maxSend<minSend || (maxSend==minSend && remain<minReceive)){
			minSend = maxSend;
			minReceive = remain;
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
		for(int i=1; i<=n; i++){
			if(dist[index]+weight[index][i]==dist[i]){
				if(dfs(i,remain,maxSend)){
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
	cin >> cmax >> n >> sp >> m;

	stations.resize(n+1);
	dist.assign(n+1,MAXIMUM);
	visited.assign(n+1,false);
	weight.resize(n+1);
	for(int i=0; i<n+1; i++){
		weight[i].assign(n+1,MAXIMUM);
	}

	for(int i=1; i<=n; i++){
		cin >> stations[i];
	}

	for(int i=0; i<m; i++){
		int si,sj;

		cin >> si >> sj;
		cin >> weight[si][sj];
		weight[sj][si] = weight[si][sj];
	}

	//Dijkstra
	visited[0] = 1;
	dist[0] = 0;
	int index = 0;
	for(int i=0; i<n; i++){
		int min = MAXIMUM;
		int nextIndex;
		for(int j=1; j<=n; j++){
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
		if(min==MAXIMUM){
			break;
		}
		index = nextIndex;
		visited[index] = 1;
	}

	stations[0] = cmax/2;
	dfs(0,0,0);

	cout << minSend << " ";
	bool first = true;
	while(!path.empty()){
		if(first){
			first = false;
		}
		else{
			cout << "->";
		}
		cout << path.top();
		path.pop();
	}
	cout << " " << minReceive;

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cstdint>
#include <cmath>
using namespace std;

#define INF 0x0fffffff

int cMax, n, sp, m, minSend = INF, minBack = INF;
vector<int> stations, dist, path;
vector<vector<int>> weight;

void dfs(int cur, int sent, int remain, int restDist, vector<int> tmp){
	if (restDist < 0 || (restDist == 0 && cur != sp)){
		return;
	}
	tmp.push_back(cur);
	remain += stations[cur] - cMax / 2;
	if (remain < 0){
		sent -= remain;
		remain = 0;
	}
	if (cur == sp){
		if (minSend > sent || (minSend == sent &&minBack > remain)){
			minSend = sent;
			minBack = remain;
			path = tmp;
		}
	}
	else{
		for (int i = 1; i <= n; ++i){
			if (dist[cur] + weight[cur][i] == dist[i]){
				dfs(i, sent, remain, restDist - weight[cur][i], tmp);
			}
		}
	}
}

int main(){
	cin >> cMax >> n >> sp >> m;
	stations.resize(n + 1);
	dist.assign(n + 1, INF);
	weight.assign(n + 1, vector<int>(n + 1, INF));
	stations[0] = cMax / 2;
	for (int i = 1; i <= n; ++i){
		cin >> stations[i];
	}
	for (int i = 0; i < m; ++i){
		int s1, s2;
		cin >> s1 >> s2;
		cin >> weight[s1][s2];
		weight[s2][s1] = weight[s1][s2];
	}

	vector<bool> visited(n + 1, 0);
	visited[0] = 1;
	dist[0] = 0;
	int index = 0;
	for (int i = 0; i < n; ++i){
		int minDist = INF;
		int nextIndex;
		for (int j = 1; j <= n; ++j){
			if (!visited[j]){
				dist[j] = min(dist[j], dist[index] + weight[index][j]);
				if (dist[j] < minDist){
					minDist = dist[j];
					nextIndex = j;
				}
			}
		}
		if (minDist == INF){
			break;
		}
		index = nextIndex;
		visited[index] = 1;
	}
	dfs(0, 0, 0, dist[sp], {});
	cout << minSend << " ";
	for (int i = 0; i < path.size(); ++i){
		if (i){
			cout << "->";
		}
		cout << path[i];
	}
	cout << " " << minBack;

	system("pause");
	return 0;
}