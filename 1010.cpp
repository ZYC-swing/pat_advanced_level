//1010.Radix
/*
Given a pair of positive integers, for example, 6 and 110, can this equation 6 = 110 be true? The answer is "yes", if 6 is a decimal number and 110 is a binary number.

Now for any pair of positive integers N1 and N2, your task is to find the radix of one number while that of the other is given.

Input Specification:

Each input file contains one test case. Each case occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit is less than its radix and is chosen from the set {0-9, a-z} where 0-9 represent the decimal numbers 0-9, and a-z represent the decimal numbers 10-35. The last number "radix" is the radix of N1 if "tag" is 1, or of N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the other number so that the equation N1 = N2 is true. If the equation is impossible, print "Impossible". If the solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
*/
#include <iostream>
#include <string>
using namespace std;

int minradix(string str){
	int radix=2;
	for(int i=0;i<str.length();i++){
		if(str[i]-'9'<=0){
			if(str[i]-'0'>=radix)
				radix = str[i]-'0'+1;
		}
		else{
			if(str[i]-'a'+10>=radix)
				radix = str[i]-'a'+11;
		}
	}
	return radix;
}

int char2num(char c){
	return (c-'9'<=0?c-'0':c-'a'+10);
}

long long transform(string str, int radix){
	if(radix == 10){
		return atoi(str.c_str());
	}
	else{
		long long tmp=0;
		int index=0;
		int i=str.length();
		while(i--){
			tmp = tmp*radix+char2num(str[index]);
			index++;
		}
		return tmp;
	}
}

// if s<num return -1
// if s==num return 0
// if s>num return 1
int cmp(string s, long long num, long long radix){
	int i;
	long long tmp=0;
  	long long tmp_last;
	for(i=0;i<s.length();i++){
		tmp_last = tmp;
		tmp = tmp*radix+char2num(s[i]);
		if(tmp>num||tmp<tmp_last)
			return 1;
	}
	if(tmp==num)
		return 0;
	else
		return -1;
}

int main(){
	string n[2];
	int tag;
	long long radix;

	cin >> n[0] >> n[1] >> tag >> radix;
	long long num = transform(n[tag-1],radix);
	int min_radix;
	long long max_radix;
	long long mid_radix;
	min_radix = minradix(n[2-tag]);
	max_radix = num+1;
	//需要实验的数只有1位的情况要特殊处理
	if(n[2-tag].length()==1){
		if(transform(n[2-tag],min_radix)==num)
			cout << min_radix;
		else
			cout << "Impossible";
	}
	else{
		while(min_radix<=max_radix){
			mid_radix = min_radix+(max_radix-min_radix)/2;
			if(cmp(n[2-tag],num,mid_radix)==0)
				break;
			else if(cmp(n[2-tag],num,mid_radix)<0)
				min_radix = mid_radix+1;
			else
				max_radix = mid_radix-1;
		}
		if(min_radix<=max_radix)
			cout << mid_radix;
		else
			cout << "Impossible";
	}

	system("pause");
	return 0;
}


//第二次刷
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long string2num(string str, long long radix){
	long long res = 0;
	for (int i = 0; i < str.length(); ++i){
		int tmp = str[i] <= '9' ? str[i] - '0' : str[i] - 'a' + 10;
		res = res * radix + tmp;
	}
	return res;
}

int main(){
	string n1, n2;
	int tag, radix;

	cin >> n1 >> n2 >> tag >> radix;
	if (tag == 2){
		swap(n1, n2);
	}
	long long goal = string2num(n1, radix);

	char tmp = n2[0];
	for (int i = 1; i < n2.length(); ++i){
		tmp = max(tmp, n2[i]);
	}
	long long left, right, res = 0;
	left = tmp <= '9' ? tmp - '0' + 1 : tmp - 'a' + 11;
	right = goal;
	if (n2.length() == 1){
		if (string2num(n2, left) == goal){
			cout << left;
		}
		else{
			cout << "Impossible";
		}
	}
	else{
		while (left < right){
			long long mid = left + ((right - left) >> 1);
			res = string2num(n2, mid);
			if (res < 0 || res > goal){
				right = mid - 1;
			}
			else if (res < goal){
				left = mid + 1;
			}
			else{
				right = mid;
			}
		}
		if (string2num(n2, left) == goal){
			cout << left;
		}
		else{
			cout << "Impossible";
		}
	}
	system("pause");
	return 0;
}