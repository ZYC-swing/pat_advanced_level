//1033. To Fill or Not to Fill
/*
With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive numbers: Cmax (<= 100), the maximum capacity of the tank; D (<=30000), the distance between Hangzhou and the destination city; Davg (<=20), the average distance per unit gas that the car can run; and N (<= 500), the total number of gas stations. Then N lines follow, each contains a pair of non-negative numbers: Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, for i=1,...N. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print "The maximum travel distance = X" where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXIMUM 1000000.0

typedef struct{
	float price;
	int dist;
}station;

bool cmp(station s1, station s2){
	return s1.dist<s2.dist;
}

int main(int argc, char const *argv[])
{
	int Cmax,Dist,Davg,N;
	vector<station> stations;
	station tmp;

	cin >> Cmax >> Dist >> Davg >> N;
	for(int i=0; i<N; i++){
		cin >> tmp.price >> tmp.dist;
		stations.push_back(tmp);
	}
	sort(stations.begin(),stations.end(),cmp);

	//起点没加油站
	if(stations[0].dist>0){
		cout << "The maximum travel distance = 0.00";
		system("pause");
		return 0;
	}

	float currCost = 0.0;
	float currDist = 0.0;
	float currCap = 0.0;
	int maxDist = Cmax*Davg;
	int index = 0;
	bool flag = false;
	/*
	1.	前maxDist有终点
		1.1.	油够用，直接走
		1.2.	油不够，前方加油站里有油价更低的，将油加到能够走到最近的油价更低的加油站（若本来就够则不加）
		1.3.	油不够，在这个加油站加到恰能走到终点的油
	2.	前maxDist没有终点，有加油站
		2.1.	前方加油站里有油价更低的，将油加到能够走到最近的油价更低的加油站（若本来就够则不加）
		2.2.	前方没有油价更低的，在这个加油站加满油，走到前面价格最低的加油站
	3.	前maxDist没有终点，也没有加油站
		加满油，能走多远走多远
	*/
	while(1){
		//1.
		if(currDist+maxDist>=Dist){
			//1.1.
			if(currDist+currCap*Davg>=Dist){
				flag = true;
				break;
			}
			else{
				int nearestIndex = N;
				for(int i=index+1; i<N; i++){
					if(stations[i].price<=stations[index].price){
						nearestIndex = i;
						break;
					}
				}
				//1.2.
				if(nearestIndex!=N){
					if((stations[nearestIndex].dist-currDist)/Davg>currCap){
						currCost += ((stations[nearestIndex].dist-currDist)/Davg-currCap)*stations[index].price;
						currDist = stations[nearestIndex].dist;
						currCap = 0;
					}
					else{
						currCap -= (stations[nearestIndex].dist-currDist)/Davg;
						currDist = stations[nearestIndex].dist;
					}
					index = nearestIndex;
					continue;
				}
				//1.3.
				else{
					currCost += ((Dist-currDist)/Davg-currCap)*stations[index].price;
					flag = true;
					break;
				}
			}
		}
		//2.
		else if(index<N-1 && currDist+maxDist>=stations[index+1].dist){			
			float min = MAXIMUM;
			int nearestIndex = N,nextIndex;
			for(int i=index+1; i<N && currDist+maxDist>=stations[i].dist; i++){
				if(stations[i].price<min){
					min = stations[i].price;
					nextIndex = i;
				}
				if(stations[i].price<=stations[index].price && i<nearestIndex){
					nearestIndex = i;
				}
			}
			//2.1.
			if(min<=stations[index].price){
				if((stations[nearestIndex].dist-currDist)/Davg>currCap){
					currCost += ((stations[nearestIndex].dist-currDist)/Davg-currCap)*stations[index].price;
					currDist = stations[nearestIndex].dist;
					currCap = 0;
				}
				else{
					currCap -= (stations[nearestIndex].dist-currDist)/Davg;
					currDist = stations[nearestIndex].dist;
				}
				index = nearestIndex;
				continue;
			}
			//2.2.
			else{
				currCost += (Cmax-currCap)*stations[index].price;
				currCap = Cmax-(stations[nextIndex].dist-currDist)/Davg;
				currDist = stations[nextIndex].dist;
				index = nextIndex;
				continue;
			}
		}
		//3.
		else{
			currDist = currDist+maxDist;
			break;
		}
	}

	if(flag){
		printf("%.2f", currCost);
	}
	else{
		printf("The maximum travel distance = %.2f", currDist);
	}

	system("pause");
	return 0;
}