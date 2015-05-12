//1007.Maximum Subsequence Sum
/*
Given a sequence of K integers { N1, N2, ..., NK }. A continuous subsequence is defined to be { Ni, Ni+1, ..., Nj } where 1 <= i <= j <= K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (<= 10000). The second line contains K numbers, separated by a space.

Output Specification:

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
	//扫描过程中的工作左右下标
	int workLeftIndex,workRightIndex;
	//扫描过程中的最大子串对应的起始、终点数值
	int maxLeft,maxRight;
	int maxSum,sum,k,num;
	vector<int> seq;

	cin >> k;
	for(int i=0; i<k; i++){
		cin >> num;
		seq.push_back(num);
	}

	maxSum = -1;
	maxLeft = seq.at(0);
	maxRight = seq.at(k-1);
	workLeftIndex = workRightIndex = 0;
	while(workLeftIndex<k){
		while(workLeftIndex<k && seq.at(workLeftIndex)<0)
			workLeftIndex++;
		if(workLeftIndex>=k)
			break;
		sum = 0;
		for(workRightIndex = workLeftIndex; workRightIndex<k && sum>=0; workRightIndex++){
			sum += seq.at(workRightIndex);
			if(sum>maxSum){
				maxSum = sum;
				maxLeft = seq.at(workLeftIndex);
				maxRight = seq.at(workRightIndex);
			}
		}
		workLeftIndex = workRightIndex;
	}

	if(maxSum>=0)
		cout << maxSum;
	else
		cout << 0;
	cout << " " <<  maxLeft << " " << maxRight;

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	vector<int> vec;
	int k, maxSum = -1, tmpSum = 0, left = 0, right = 0, maxLeft = 0, maxRight;

	cin >> k;
	vec.resize(k);
	maxRight = k - 1;
	for (int i = 0; i < k; ++i){
		cin >> vec[i];
		tmpSum += vec[i];
		if (tmpSum > maxSum){
			maxLeft = left;
			maxRight = right;
			maxSum = tmpSum;
		}
		if (tmpSum < 0){
			left = i + 1;
			right = i;
			tmpSum = 0;
		}
		++right;
	}
	cout << max(maxSum, 0) << " " << vec[maxLeft] << " " << vec[maxRight];
	system("pause");
	return 0;
}