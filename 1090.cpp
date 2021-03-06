//1090. Highest Price in Supply Chain
/*
A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or distribute them in a price that is r% higher than P. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.

Input Specification:

Each input file contains one test case. For each case, The first line contains three positive numbers: N (<=105), the total number of the members in the supply chain (and hence they are numbered from 0 to N-1); P, the price given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer. Then the next line contains N numbers, each number Si is the index of the supplier for the i-th member. Sroot for the root supplier is defined to be -1. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the highest price we can expect from some retailers, accurate up to 2 decimal places, and the number of retailers that sell at the highest price. There must be one space between the two numbers. It is guaranteed that the price will not exceed 1010.

Sample Input:
9 1.80 1.00
1 5 4 4 -1 4 5 3 6
Sample Output:
1.85 2
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

int maxDepth = 0,cnt = 0;
vector<vector<int>> net;

void dfs(int index, int depth){
	depth++;
	if(net[index].size()==0){
		if(depth>maxDepth){
			maxDepth = depth;
			cnt = 1;
		}
		else if(depth==maxDepth){
			cnt++;
		}
	}
	else{
		for(int i=0; i<net[index].size(); i++){
			dfs(net[index][i],depth);
		}
	}
}

int main(int argc, char const *argv[])
{
	int n,rootId;
	double p,r;

	cin >> n >> p >> r;
	net.resize(n);
	for(int i=0; i<n; i++){
		int num;
		cin >> num;
		if(num==-1){
			rootId = i;
			continue;
		}
		net[num].push_back(i);
	}

	dfs(rootId,-1);

	printf("%.2lf %d", p*pow(1+0.01*r,maxDepth), cnt);

	system("pause");
	return 0;
}