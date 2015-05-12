//1003.Emergency
/*
As an emergency rescue team leader of a city, you are given a special map of your country. The map shows several scattered cities connected by some roads. Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map. When there is an emergency call to you from some other city, your job is to lead your men to the place as quickly as possible, and at the mean time, call up as many hands on the way as possible.

Input

Each input file contains one test case. For each test case, the first line contains 4 positive integers: N (<= 500) - the number of cities (and the cities are numbered from 0 to N-1), M - the number of roads, C1 and C2 - the cities that you are currently in and that you must save, respectively. The next line contains N integers, where the i-th integer is the number of rescue teams in the i-th city. Then M lines follow, each describes a road with three integers c1, c2 and L, which are the pair of cities connected by a road and the length of that road, respectively. It is guaranteed that there exists at least one path from C1 to C2.

Output

For each test case, print in one line two numbers: the number of different shortest paths between C1 and C2, and the maximum amount of rescue teams you can possibly gather.
All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.

Sample Input
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
Sample Output
2 4

Sample Input:
7 8 0 6
1 2 3 4 5 6 7
0 1 2
0 2 1
1 3 1
2 3 2
3 4 3
3 5 4
4 6 4
5 6 3
Sample Output:
4 28
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define INF 0x0fffffff//距离无穷

int n,m,start,dest,maxNum = 0,cnt = 0;
vector<int> dist;
vector<int> teams;
vector<vector<int>> weight;

void dfs(int index, int num){
	num += teams[index];
	if(index==start){
		cnt++;
		if(num>maxNum){
			maxNum = num;
		}
	}
	else{
		for(int i=0; i<n; i++){
			if(dist[i]+weight[i][index]==dist[index]){
				dfs(i,num);
			}
		}
	}
}

int main(){
	cin >> n >> m >> start >> dest;
	
	teams.resize(n);
	weight.resize(n);
	for(int i=0; i<n; i++){
		weight[i].assign(n,INF);
	}

	for(int i=0; i<n; i++){
		cin >> teams[i];
	}

	for(int i=0; i<m; i++){
		int c[2];

		cin >> c[0] >> c[1];
		cin >> weight[c[0]][c[1]];
		weight[c[1]][c[0]] = weight[c[0]][c[1]];
	}

	//Dijkstra
	vector<bool> visited;
	visited.assign(n,0);
	dist.assign(n,INF);
	visited[start] = 1;
	dist[start] = 0;
	int index = start;
	for(int i=0; i<n-1; i++){
		int min = INF;
		int nextIndex;
		for(int j=0; j<n; j++){
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
		visited[index] = 1;
	}

	dfs(dest,0);

	cout << cnt << " " << maxNum;

	system("pause");
	return 0;
}