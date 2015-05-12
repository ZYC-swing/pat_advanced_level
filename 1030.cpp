//1030. Travel Plan
/*
A traveler's map gives the distances between cities along the highways, together with the cost of each highway. Now you are supposed to write a program to help a traveler to decide the shortest path between his/her starting city and the destination. If such a shortest path is not unique, you are supposed to output the one with the minimum cost, which is guaranteed to be unique.

Input Specification:

Each input file contains one test case. Each case starts with a line containing 4 positive integers N, M, S, and D, where N (<=500) is the number of cities (and hence the cities are numbered from 0 to N-1); M is the number of highways; S and D are the starting and the destination cities, respectively. Then M lines follow, each provides the information of a highway, in the format:

City1 City2 Distance Cost

where the numbers are all integers no more than 500, and are separated by a space.

Output Specification:

For each test case, print in one line the cities along the shortest path from the starting point to the destination, followed by the total distance and the total cost of the path. The numbers must be separated by a space and there must be no extra space at the end of output.

Sample Input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
Sample Output
0 2 3 3 40
*/
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

#define MAXN 500
#define INF 0x0fffffff

stack<int> path;
bool visited[MAXN];
int weight[MAXN][MAXN],cost[MAXN][MAXN],dist[MAXN];
int minCost;
int n,m,start,dest;

bool dfs(int index, int restDist, int totalCost){
	if(restDist<=0 && index!=dest){
		visited[index] = 1;
		return false;
	}
	if(index==dest){
		if(totalCost<minCost){
			while(!path.empty()){
				path.pop();
			}
			minCost = totalCost;
			path.push(index);
			return true;
		}
		else{
			return false;
		}
	}
	else{
		visited[index] = 1;
		bool flag=false,ret=false;
		for(int i=0; i<n; i++){
			if(!visited[i] && weight[index][i]<=restDist){
				flag = dfs(i, restDist-weight[index][i], totalCost+cost[index][i]);
				if(flag){
					path.push(index);
					ret = true;
				}
			}
		}
		return ret;
	}
}

int main(int argc, char const *argv[])
{
	cin >> n >> m >> start >> dest;
	for(int i=0; i<n; i++){
		visited[i] = 0;
		dist[i] = INF;
		for(int j=0; j<i; j++){
			weight[i][j] = weight[j][i] = INF;
			cost[i][j] = cost[j][i] = INF;
		}
		weight[i][i] = 0;
		cost[i][i] = 0;
	}
		
	int city1,city2,d,c;
	for(int i=0; i<m; i++){
		cin >> city1 >> city2 >> d >> c;
		weight[city1][city2] = weight[city2][city1] = d;
		cost[city1][city2] = cost[city2][city1] = c;
	}

	//Dijkstra
	visited[start] = 1;
	dist[start] = 0;
	for(int i=0; i<n; i++){
		if(i!=start && weight[start][i]<INF){
			dist[i] = weight[start][i];
		}
	}

	for(int i=1; i<=n-1; i++){
		int min = INF;
		int index;
		for(int i=0; i<n; i++){
			if(!visited[i] && dist[i]<min){
				min = dist[i];
				index = i;
			}
		}
		visited[index] = 1;
		for(int i=0; i<n; i++){
			if(!visited[i] && dist[index]+weight[index][i]<dist[i]){
				dist[i] = dist[index]+weight[index][i];
			}
		}
	}

	int minDist = dist[dest];
	minCost = INF;
	int totalCost = 0;
	memset(visited,0,n*sizeof(bool));
	dfs(start,minDist,totalCost);

	while(!path.empty()){
		cout << path.top() << " ";
		path.pop();
	}
	cout << minDist << " " << minCost;

	system("pause");
	return 0;
}