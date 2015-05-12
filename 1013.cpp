//1013. Battle Over Cities
/*
It is vitally important to have all the cities connected by highways in a war. If a city is occupied by the enemy, all the highways from/toward that city are closed. We must know immediately if we need to repair any other highways to keep the rest of the cities connected. Given the map of cities which have all the remaining highways marked, you are supposed to tell the number of highways need to be repaired, quickly.

For example, if we have 3 cities and 2 highways connecting city1-city2 and city1-city3. Then if city1 is occupied by the enemy, we must have 1 highway repaired, that is the highway city2-city3.

Input

Each input file contains one test case. Each case starts with a line containing 3 numbers N (<1000), M and K, which are the total number of cities, the number of remaining highways, and the number of cities to be checked, respectively. Then M lines follow, each describes a highway by 2 integers, which are the numbers of the cities the highway connects. The cities are numbered from 1 to N. Finally there is a line containing K numbers, which represent the cities we concern.

Output

For each of the K cities, output in a line the number of highways need to be repaired if that city is lost.

Sample Input
3 2 3
1 2
1 3
1 2 3
Sample Output
1
0
0
*/
#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1000

int road[MAXN][MAXN],visited[MAXN];//visited表示在dfs中是否被访问到

void dfs(int j, int check, int n){
	visited[j] = 1;
	for(int i=0; i<n; i++){
		if(i!=j && i+1!=check && road[j][i] && !visited[i]){
			dfs(i,check,n);
		}
	}
}

int main(int argc, char const *argv[])
{
	int n,m,k,c1,c2;
	int check,count//check代表要检测的城市，count表示连通分量数目
	memset(road,0,sizeof(road));

	cin >> n >> m >> k;
	for(int i=0; i<m; i++){
		cin >> c1 >> c2;
		road[c1][c2] = road[c2][c1] = 1;
	}

	for(int i=0; i<k; i++){
		cin >> check;
		memset(visited,0,sizeof(visited));
		count = 0;
		for(int j=0; j<n; j++){
			if (j+1!=check && !visited[j])
			{
				count++;
				dfs(j,check,n);
			}
		}
		cout << count-1;
		if (i!=k-1)
		{
			cout << endl;
		}
	}

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> edge;
vector<bool> visited;

void dfs(int cur, int &n, int &mark){
	visited[cur] = 1;
	for (int i = 1; i <= n; ++i){
		if (i == mark){
			continue;
		}
		if (!visited[i] && edge[cur][i]){
			dfs(i, n, mark);
		}
	}
}

int main(){
	int n, m, k;
	cin >> n >> m >> k;
	edge.assign(n + 1, vector<bool>(n + 1, 0));
	for (int i = 0; i < m; ++i){
		int c1, c2;
		cin >> c1 >> c2;
		edge[c1][c2] = edge[c2][c1] = 1;
	}
	for (int i = 0; i < k; ++i){
		int mark, cnt = 0;
		visited.assign(n + 1, 0);
		cin >> mark;
		for (int i = 1; i <= n; ++i){
			if (i == mark || visited[i]){
				continue;
			}
			++cnt;
			dfs(i, n, mark);
		}
		cout << cnt - 1 << endl;
	}
	system("pause");
	return 0;
}