//1091. Acute Stroke
/*
One important factor to identify acute stroke (急性脑卒中) is the volume of the stroke core. Given the results of image analysis in which the core regions are identified in each MRI slice, your job is to calculate the volume of the stroke core.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive integers: M, N, L and T, where M and N are the sizes of each slice (i.e. pixels of a slice are in an M by N matrix, and the maximum resolution is 1286 by 128); L (<=60) is the number of slices of a brain; and T is the integer threshold (i.e. if the volume of a connected core is less than T, then that core must not be counted).

Then L slices are given. Each slice is represented by an M by N matrix of 0's and 1's, where 1 represents a pixel of stroke, and 0 means normal. Since the thickness of a slice is a constant, we only have to count the number of 1's to obtain the volume. However, there might be several separated core regions in a brain, and only those with their volumes no less than T are counted. Two pixels are "connected" and hence belong to the same region if they share a common side, as shown by Figure 1 where all the 6 red pixels are connected to the blue one.


Figure 1
Output Specification:

For each case, output in a line the total volume of the stroke core.

Sample Input:
3 4 5 2
1 1 1 1
1 1 1 1
1 1 1 1
0 0 1 1
0 0 1 1
0 0 1 1
1 0 1 1
0 1 0 0
0 0 0 0
1 0 1 1
0 0 0 0
0 0 0 0
0 0 0 1
0 0 0 1
1 0 0 0
Sample Output:
26
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<vector<bool>>> valid;
vector<vector<vector<int>>> pre;
int m,n,l,t;

void init(){
	for(int i=0; i<l; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				pre[i][j][k] = i*m*n+j*n+k;
			}
		}
	}
}

int root(int a, int b, int c){
	if(a*m*n+b*n+c!=pre[a][b][c]){
		int x,y,z;
		z = pre[a][b][c]/(m*n);
		x = (pre[a][b][c]%(m*n))/n;
		y = (pre[a][b][c])%n;
		pre[a][b][c] = root(z,x,y);
	}
	return pre[a][b][c];
}

void merge(int a1, int b1, int c1, int a2, int b2, int c2){
	int x[2],y[2],z[2],roots[2];

	roots[0] = root(a1,b1,c1);
	roots[1] = root(a2,b2,c2);
	for(int i=0; i<2; i++){
		z[i] = roots[i]/(m*n);
		x[i] = (roots[i]%(m*n))/n;
		y[i] = roots[i]%n;
	}

	if(roots[0]!=roots[1]){
		pre[z[0]][x[0]][y[0]] = pre[z[1]][x[1]][y[1]];
	}
}

int main(int argc, char const *argv[])
{
	cin >> m >> n >> l >> t;
	pre.resize(l,vector<vector<int>>(m,vector<int>(n)));
	valid.assign(l,vector<vector<bool>>(m,vector<bool>(n,0)));

	for(int i=0; i<l; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				cin >> pre[i][j][k];
				if(pre[i][j][k]){
					valid[i][j][k] = 1;
				}
			}
		}
	}

	init();

	for(int i=0; i<l; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				if(valid[i][j][k]){
					if(i>=1 && valid[i-1][j][k]){
						merge(i,j,k,i-1,j,k);
					}
					if(j>=1 && valid[i][j-1][k]){
						merge(i,j,k,i,j-1,k);
					}
					if(k>=1 && valid[i][j][k-1]){
						merge(i,j,k,i,j,k-1);
					}
				}
			}
		}
	}

	map<int,int> volumes;
	for(int i=0; i<l; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				if(valid[i][j][k]){
					volumes[root(i,j,k)]++;
				}
			}
		}
	}

	int cnt = 0;
	for(map<int,int>::iterator it=volumes.begin(); it!=volumes.end(); it++){
		if(it->second>=t){
			cnt += it->second;
		}
	}

	cout << cnt;

	system("pause");
	return 0;
}