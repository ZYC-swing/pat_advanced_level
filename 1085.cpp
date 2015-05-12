//1085. Perfect Sequence
/*
Given a sequence of positive integers and another positive integer p. The sequence is said to be a "perfect sequence" if M <= m * p where M and m are the maximum and minimum numbers in the sequence, respectively.

Now given a sequence and a parameter p, you are supposed to find from the sequence as many numbers as possible to form a perfect subsequence.

Input Specification:

Each input file contains one test case. For each case, the first line contains two positive integers N and p, where N (<= 105) is the number of integers in the sequence, and p (<= 109) is the parameter. In the second line there are N positive integers, each is no greater than 109.

Output Specification:

For each test case, print in one line the maximum number of integers that can be chosen to form a perfect subsequence.

Sample Input:
10 8
2 3 20 4 5 1 6 7 8 9
Sample Output:
8
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> num,dp;//dp[i]代表以i为结尾的满足要求最长数字串的第一个数字下标
	long long n,p;

	cin >> n >> p;
	num.resize(n);
	dp.resize(n);
	for(int i=0; i<n; i++){
		cin >> num[i];
	}
	sort(num.begin(),num.end());
	int maxLen = 1;
	dp[0] = 0;
	for(int i=1; i<n; i++){
		if(num[dp[i-1]]*p>=num[i]){
			dp[i] = dp[i-1];
		}
		else{
			int index = dp[i-1]+1;
			while(num[index]*p<num[i]){
				index++;
			}
			dp[i] = index;
		}
		if(i-dp[i]+1>maxLen){
			maxLen = i-dp[i]+1;
		}
	}

	cout << maxLen;

	system("pause");
	return 0;
}