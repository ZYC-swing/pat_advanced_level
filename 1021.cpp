//1021. Deepest Root
/*
A graph which is connected and acyclic can be considered a tree. The height of the tree depends on the selected root. Now you are supposed to find the root that results in a highest tree. Such a root is called the deepest root.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=10000) which is the number of nodes, and hence the nodes are numbered from 1 to N. Then N-1 lines follow, each describes an edge by given the two adjacent nodes' numbers.

Output Specification:

For each test case, print each of the deepest roots in a line. If such a root is not unique, print them in increasing order of their numbers. In case that the given graph is not a tree, print "Error: K components" where K is the number of connected components in the graph.

Sample Input 1:
5
1 2
1 3
1 4
2 5
Sample Output 1:
3
4
5
Sample Input 2:
5
1 3
1 4
2 5
3 4
Sample Output 2:
Error: 2 components
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 10000

int n,depth[MAXN],visited[MAXN],farthest[MAXN],valid[MAXN];
vector<int> deepest;
vector<vector<int>> edge(MAXN);

void dfs(int start, int curr, int currDepth){
	visited[curr] = 1;
	if(currDepth>depth[start]){
		depth[start] = currDepth;
		deepest.clear();
		deepest.push_back(curr);
	}
	else if(currDepth==depth[start]){
		deepest.push_back(curr);
	}
	for(vector<int>::iterator it=edge[curr].begin(); it!=edge[curr].end(); it++){
		if(!visited[*it]){
			dfs(start, *it, currDepth+1);
		}
	}
}

int main(int argc, char const *argv[])
{
	cin >> n;
	memset(depth,0,n*sizeof(int));
	memset(valid,0,n*sizeof(int));

	int a,b;
	for(int i=0; i<n-1; i++){
		cin >> a >> b;
		edge[a-1].push_back(b-1);
		edge[b-1].push_back(a-1);
	}

	//DFS
	memset(visited,0,n*sizeof(int));
	int components = 0;
	for(int i=0; i<n; i++){
		if(!visited[i]){
			components++;
			dfs(i,i,1);
		}
	}
	if(components>1){
		cout << "Error: " << components << " components";
		system("pause");
		return 0;
	}
	else{
		int index = deepest.front();
		for(vector<int>::iterator it = deepest.begin(); it!=deepest.end(); it++){
			valid[(*it)] = 1;
		}

		memset(visited,0,n*sizeof(int));
		dfs(index,index,1);
		for(vector<int>::iterator it = deepest.begin(); it!=deepest.end(); it++){
			valid[(*it)] = 1;
		}
	}
	for(int i=0; i<n; i++){
		if(valid[i]){
			cout << i+1 << endl;
		}
	}

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<vector<bool>> conn;

void dfs(int cur, int depth, int &maxDepth, vector<bool> &visited, vector<int> &res){
	visited[cur] = 1;
	if (depth > maxDepth){
		maxDepth = depth;
		res.clear();
	}
	if (depth == maxDepth){
		res.push_back(cur);
	}
	for (int i = 0; i < n; ++i){
		if (!visited[i] && conn[cur][i]){
			dfs(i, depth + 1, maxDepth, visited, res);
		}
	}
}

int main(){
	cin >> n;
	conn.assign(n, vector<bool>(n, 0));
	for (int i = 0; i < n - 1; ++i){
		int a, b;
		cin >> a >> b;
		--a, --b;
		conn[a][b] = conn[b][a] = 1;
	}
	int cnt = 0;
	vector<bool> visited(n, 0);
	vector<int> first, second;
	for (int i = 0; i < n; ++i){
		if (!visited[i]){
			++cnt;
			int maxDepth = 0;
			dfs(i, 1, maxDepth, visited, first);
		}
	}
	if (cnt > 1){
		cout << "Error: " << cnt << " components";
	}
	else{
		visited.assign(n, 0);
		int maxDepth = 0;
		dfs(first[0], 1, maxDepth, visited, second);
		for (auto i : second){
			first.push_back(i);
		}
		sort(first.begin(), first.end());
		first.erase(unique(first.begin(), first.end()), first.end());
		for (auto i : first){
			cout << i + 1 << endl;
		}
	}

	system("pause");
	return 0;
}