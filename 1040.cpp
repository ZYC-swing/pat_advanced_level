//1040. Longest Symmetric String
/*
Given a string, you are supposed to output the length of the longest symmetric sub-string. For example, given "Is PAT&TAP symmetric?", the longest symmetric sub-string is "s PAT&TAP s", hence you must output 11.

Input Specification:

Each input file contains one test case which gives a non-empty string of length no more than 1000.

Output Specification:

For each test case, simply print the maximum length in a line.

Sample Input:
Is PAT&TAP symmetric?
Sample Output:
11
*/

//Manacher算法
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	string str,tmp;
	vector<int> p;

	getline(cin,str);
	int len = str.length();
	p.resize(2*len+1);
	for(int i=0; i<len; i++){
		tmp.push_back('#');
		tmp.push_back(str[i]);
	}
	tmp.push_back('#');

	len = 2*len+1;
	int mx,id;

	mx = 1;
	id = 0;
	p[0] = 1;
	for(int i=1; i<len; i++){
		if(i<mx){
			p[i] = min(mx-i,p[2*id-i]);
		}
		else{
			p[i] = 1;
		}
		while(i+p[i]<len && i-p[i]>=0 && tmp[i+p[i]]==tmp[i-p[i]]){
			p[i]++;
		}
		if(i+p[i]-1>mx){
			mx = i+p[i]-1;
			id = i;
		}
	}

	int maxLen = 0;
	for(int i=1; i<len; i++){
		maxLen = max(maxLen,p[i]-1);
	}

	cout << maxLen;

	system("pause");
	return 0;
}

// #include <iostream>
// #include <stack>
// #include <string>
// using namespace std;

// bool isSymmetric(string str){
// 	stack<char> s;
// 	int len = str.length();
// 	int i;
// 	for(i=0; i<len/2; i++){
// 		s.push(str[i]);
// 	}
// 	if(len%2==1)
// 		i++;
// 	for(; i<len; i++){
// 		if(s.top()==str[i]){
// 			s.pop();
// 		}
// 		else{
// 			return false;
// 		}
// 	}
	
// 	return true;
// }

// int main(int argc, char const *argv[])
// {
// 	string str,subStr;

// 	getline(cin,str,'\n');
// 	int len = str.length();

// 	int left,right,mid,tmpLen,maxEven,maxOdd;

// 	maxEven = maxOdd = 0;
// 	int even = len/2;
// 	left = 1;
// 	right = even;
// 	while(left<=right){
// 		mid = (left+right)/2;
// 		tmpLen = mid*2;
// 		int index;
// 		for(index=0; index+tmpLen-1<len; index++){
// 			subStr.assign(str,index,tmpLen);
// 			if(isSymmetric(subStr)){
// 				maxEven = tmpLen;
// 				break;
// 			}
// 		}
// 		if(index+tmpLen-1<len){
// 			left = mid+1;
// 		}
// 		else{
// 			right = mid-1;
// 		}
// 	}
	
// 	int odd = len-even;
// 	left = 1;
// 	right = odd;
// 	while(left<=right){
// 		mid = (left+right)/2;
// 		tmpLen = mid*2-1;
// 		int index;
// 		for(index=0; index+tmpLen-1<len; index++){
// 			subStr.assign(str,index,tmpLen);
// 			if(isSymmetric(subStr)){
// 				maxOdd = tmpLen;
// 				break;
// 			}
// 		}
// 		if(index+tmpLen-1<len){
// 			left = mid+1;
// 		}
// 		else{
// 			right = mid-1;
// 		}
// 	}

// 	if(maxEven>maxOdd){
// 		cout << maxEven;
// 	}
// 	else{
// 		cout << maxOdd;
// 	}

// 	system("pause");
// 	return 0;
// }

//第二次刷
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
	string str;
	getline(cin, str);
	vector<char> vec;
	vec.push_back('#');
	for (auto i : str){
		vec.push_back(i);
		vec.push_back('#');
	}
	int maxLen = 1;
	for (int i = 1; i < vec.size() - 1; ++i){
		int left, right;
		for (left = right = i; left >= 0 && right < vec.size() && vec[left] == vec[right]; --left, ++right);
		maxLen = max(maxLen, right - left - 1);
	}
	cout << maxLen / 2;
	system("pause");
	return 0;
}

//DP
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
	string str;
	getline(cin, str);
	int len = str.length();
	vector<vector<bool>> dp(len, vector<bool>(len, 0));
	for (int i = 0; i < len; ++i){
		dp[i][i] = 1;
	}
	int maxLen = 1;
	for (int i = 1; i < len; ++i){
		for (int j = i - 1; j >= 0; --j){
			dp[j][i] = 0;
			if (str[j] == str[i] && (i - j < 2 || dp[j + 1][i - 1])){
				dp[j][i] = 1;
				maxLen = max(maxLen, i - j + 1);
			}
		}
	}
	cout << maxLen;
	system("pause");
	return 0;
}