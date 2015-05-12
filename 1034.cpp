//1034. Head of a Gang
/*
One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between A and B, we say that A and B is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threshold K. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

Input Specification:

Each input file contains one test case. For each case, the first line contains two positive numbers N and K (both less than or equal to 1000), the number of phone calls and the weight threthold, respectively. Then N lines follow, each in the following format:

Name1 Name2 Time

where Name1 and Name2 are the names of people at the two ends of the call, and Time is the length of the call. A name is a string of three capital letters chosen from A-Z. A time length is a positive integer which is no more than 1000 minutes.

Output Specification:

For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

Sample Input 1:
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 1:
2
AAA 3
GGG 3
Sample Input 2:
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 2:
0
*/
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef struct{
	string name;
	int weight;
	int lable;
	bool visited;
	vector<string> neighbours;
}person;

typedef struct{
	int totalWeight;
	vector<person> numbers;
}gang;

map<string,person> persons;
vector<gang> gangs;

void dfs(string name, int lable){
	persons[name].visited = 1;
	persons[name].lable = lable;
	gangs[lable].totalWeight += persons[name].weight;
	gangs[lable].numbers.push_back(persons[name]);
	for(vector<string>::iterator it=persons[name].neighbours.begin(); it!=persons[name].neighbours.end(); it++){
		if(!persons[(*it)].visited){
			dfs(*it,lable);
		}
	}
}

int main(int argc, char const *argv[])
{
	int n,threshold,id;

	id = 0;
	cin >> n >> threshold;
	for(int i=0; i<n; i++){
		string name[2];
		int timeOfCall;
		cin >> name[0] >> name[1] >> timeOfCall;
		for(int j=0; j<2; j++){
			if(persons.find(name[j])==persons.end()){
				persons[name[j]].name = name[j];
				persons[name[j]].weight = timeOfCall;
				persons[name[j]].visited = 0;
			}
			else{
				persons[name[j]].weight += timeOfCall;
			}
			persons[name[j]].neighbours.push_back(name[1-j]);
		}
	}

	//DFS
	int lable = 0;
	for(map<string,person>::iterator it=persons.begin(); it!=persons.end(); it++){
		if(!(*it).second.visited){
			gang tmp;
			tmp.totalWeight = 0;
			gangs.push_back(tmp);
			dfs((*it).first,lable);
			gangs[lable].totalWeight /= 2;
			lable++;
		}
	}

	vector<string> validGangLeader;
	for(int i=0; i<lable; i++){
		if(gangs[i].totalWeight>threshold && gangs[i].numbers.size()>2){
			int maxWeight = 0;
			string name;
			for(vector<person>::iterator it=gangs[i].numbers.begin(); it!=gangs[i].numbers.end(); it++){
				if((*it).weight>maxWeight){
					maxWeight = (*it).weight;
					name = (*it).name;
				}
			}
			validGangLeader.push_back(name);
		}
	}
	sort(validGangLeader.begin(),validGangLeader.end());
	cout << validGangLeader.size();
	for(int i=0; i<validGangLeader.size(); i++){
		cout << endl << validGangLeader[i] << " " << gangs[persons[validGangLeader[i]].lable].numbers.size();
	}

	system("pause");
	return 0;
}