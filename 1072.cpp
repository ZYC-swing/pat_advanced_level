//1072. Gas Station
/*
A gas station has to be built at such a location that the minimum distance between the station and any of the residential housing is as far away as possible. However it must guarantee that all the houses are in its service range.

Now given the map of the city and several candidate locations for the gas station, you are supposed to give the best recommendation. If there are more than one solution, output the one with the smallest average distance to all the houses. If such a solution is still not unique, output the one with the smallest index number.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive integers: N (<= 103), the total number of houses; M (<= 10), the total number of the candidate locations for the gas stations; K (<= 104), the number of roads connecting the houses and the gas stations; and DS, the maximum service range of the gas station. It is hence assumed that all the houses are numbered from 1 to N, and all the candidate locations are numbered from G1 to GM.

Then K lines follow, each describes a road in the format
P1 P2 Dist
where P1 and P2 are the two ends of a road which can be either house numbers or gas station numbers, and Dist is the integer length of the road.

Output Specification:

For each test case, print in the first line the index number of the best location. In the next line, print the minimum and the average distances between the solution and all the houses. The numbers in a line must be separated by a space and be accurate up to 1 decimal place. If the solution does not exist, simply output “No Solution”.

Sample Input 1:
4 3 11 5
1 2 2
1 4 2
1 G1 4
1 G2 3
2 3 2
2 G2 1
3 4 2
3 G3 2
4 G1 3
G2 G1 1
G3 G2 2
Sample Output 1:
G1
2.0 3.3
Sample Input 2:
2 1 2 10
1 G1 9
2 G1 20
Sample Output 2:
No Solution
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define MAXIMUM 0x0fffffff

int n,m,k,ds;
vector<bool> visited;
vector<int> dist;
vector<vector<int>> weight;

typedef struct{
	int index;
	int minDist;
	float avgDist;
}gasStation;

bool cmp(gasStation g1, gasStation g2){
	if(g1.minDist>g2.minDist){
		return 1;
	}
	else if(g1.minDist==g2.minDist && g1.avgDist<g2.avgDist){
		return 1;
	}
	else if(g1.minDist==g2.minDist && g1.avgDist==g2.avgDist && g1.index<g2.index){
		return 1;
	}
	else{
		return 0;
	}
}

int lable2index(string lable){
	int index = 0;

	if(lable[0]=='G'){
		for(int i=1; i<lable.length(); i++){
			index = index*10+lable[i]-'0';
		}
		index += n-1;
	}
	else{
		for(int i=0; i<lable.length(); i++){
			index = index*10+lable[i]-'0';
		}
		index--;
	}

	return index;
}

int main(int argc, char const *argv[])
{
	cin >> n >> m >> k >> ds;
	visited.resize(n+m);
	dist.resize(n+m);
	weight.resize(n+m,vector<int>(n+m));

	for(int i=0; i<n+m; i++){
		for(int j=0; j<=i; j++){
			if(i==j){
				weight[i][j] = 0;
			}
			else{
				weight[i][j] = weight[j][i] = MAXIMUM;
			}
		}
	}
	//0~n-1		:residential housing
	//n~n+m-1	:gas station
	for(int i=0; i<k; i++){
		string ends[2];
		int d,index[2];

		cin >> ends[0] >> ends[1] >> d;
		index[0] = lable2index(ends[0]);
		index[1] = lable2index(ends[1]);
		weight[index[0]][index[1]] = weight[index[1]][index[0]] = d;
	}
	
	vector<gasStation> stations;
	//Dijkstra
	for(int gasIndex=n; gasIndex<n+m; gasIndex++){
		visited.assign(n+m,0);
		dist.assign(n+m,MAXIMUM);
		visited[gasIndex] = 1;
		dist[gasIndex] = 0;
		bool valid = 1;
		int minDist = MAXIMUM;
		float avgDist = 0.0;
		
		int cnt = n;
		int index = gasIndex;
		//并不需要把每个节点都遍历到，只需要把n个城市遍历到即可
		while(cnt){
			int min = MAXIMUM;
			int nextIndex;
			for(int j=0; j<n+m; j++){
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
			if(min>ds){
				valid = 0;
				break;
			}
			index = nextIndex;
			visited[index] = 1;
			//编号小于n的点代表住房
			if(index<n){
				cnt--;
				if(dist[index]<minDist){
					minDist = dist[index];
				}
				avgDist += dist[index];
			}
		}
		avgDist /= n;
		if(valid){
			gasStation tmp;
			tmp.index = gasIndex;
			tmp.minDist = minDist;
			tmp.avgDist = avgDist;
			stations.push_back(tmp);
		}
	}

	if(stations.empty()){
		cout << "No Solution";
	}
	else{
		sort(stations.begin(),stations.end(),cmp);
		cout << 'G' << stations[0].index-n+1 << endl;
		printf("%d.0 %.1f", stations[0].minDist, stations[0].avgDist);
	}

	system("pause");
	return 0;
}