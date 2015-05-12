//1057. Stack
/*
Stack is one of the most fundamental data structures, which is based on the principle of Last In First Out (LIFO). The basic operations include Push (inserting an element onto the top position) and Pop (deleting the top element). Now you are supposed to implement a stack with an extra operation: PeekMedian -- return the median value of all the elements in the stack. With N elements, the median value is defined to be the (N/2)-th smallest element if N is even, or ((N+1)/2)-th if N is odd.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<= 105). Then N lines follow, each contains a command in one of the following 3 formats:

Push key
Pop
PeekMedian
where key is a positive integer no more than 105.

Output Specification:

For each Push command, insert key into the stack and output nothing. For each Pop or PeekMedian command, print in a line the corresponding returned value. If the command is invalid, print "Invalid" instead.

Sample Input:
17
Pop
PeekMedian
Push 3
PeekMedian
Push 2
PeekMedian
Push 1
PeekMedian
Pop
Pop
Push 5
Push 4
PeekMedian
Pop
Pop
Pop
Pop
Sample Output:
Invalid
Invalid
3
2
2
1
2
4
4
5
3
Invalid
*/

// #include <iostream>
// #include <stack>
// #include <set>
// #include <functional>
// #include <cstdio>
// #include <cstring>
// using namespace std;

// int main(int argc, char const *argv[])
// {
// 	stack<int> st;
// 	multiset<int> upper;
// 	multiset<int,greater<int>> lowwer;
// 	int n;

// 	scanf("%d", &n);
// 	while(n--){
// 		char command[11];
// 		int num;
		
// 		scanf("%s", command);
// 		if(strcmp(command,"Pop")==0){
// 			if(st.empty()){
// 				printf("Invalid\n");
// 			}
// 			else{
// 				printf("%d\n", st.top());
// 				if(*upper.begin()<=st.top()){
// 					upper.erase(upper.find(st.top()));
// 				}
// 				else{
// 					lowwer.erase(lowwer.find(st.top()));
// 				}
// 				st.pop();
// 				if(upper.size()==lowwer.size() && lowwer.size()>0){
// 					upper.insert(*(lowwer.begin()));
// 					lowwer.erase(lowwer.begin());
// 				}
// 				else if(upper.size()-lowwer.size()>2){
// 					lowwer.insert(*upper.begin());
// 					upper.erase(upper.begin());
// 				}
// 			}
// 		}
// 		else if(strcmp(command,"Push")==0){
// 			scanf("%d", &num);
// 			st.push(num);
// 			if(lowwer.size()>0 && *lowwer.begin()>st.top()){
// 				lowwer.insert(st.top());
// 			}
// 			else{
// 				upper.insert(st.top());
// 			}
// 			if(upper.size()==lowwer.size()){
// 				upper.insert(*(lowwer.begin()));
// 				lowwer.erase(lowwer.begin());
// 			}
// 			else if(upper.size()-lowwer.size()>2){
// 				lowwer.insert(*upper.begin());
// 				upper.erase(upper.begin());
// 			}
// 		}
// 		else{
// 			if(st.empty()){
// 				printf("Invalid\n");
// 			}
// 			else{
// 				printf("%d\n", *upper.begin());
// 			}
// 		}
// 	}

// 	system("pause");
// 	return 0;
// }

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <stack>
using namespace std;

#define MAXKEY 100000

int c[MAXKEY+1];

int lowbit(int x){
	return x&(-x);
}

void add(int index, int num){
	while(index<=MAXKEY){
		c[index] += num;
		index += lowbit(index);
	}
}

int sum(int index){
	int res = 0;

	while(index){
		res += c[index];
		index -= lowbit(index);
	}

	return res;
}

int findIndex(int n){
	int left,right,mid;

	left = 1;
	right = MAXKEY;
	while(left<right){
		mid = (left+right)/2;
		if(sum(mid)<n){
			left = mid+1;
		}
		else{
			right = mid;
		}
	}

	return left;
}

int main(int argc, char const *argv[])
{
	stack<int> ss;
	int n;

	memset(c,0,sizeof(c));
	scanf("%d", &n);
	while(n--){
		char command[11];
		scanf("%s", command);
		if(strcmp(command,"Push")==0){
			int num;
			scanf("%d", &num);
			add(num,1);
			ss.push(num);
		}
		else if(strcmp(command,"Pop")==0){
			if(ss.empty()){
				printf("Invalid\n");
			}
			else{
				printf("%d\n", ss.top());
				add(ss.top(),-1);
				ss.pop();
			}
		}
		else{
			if(ss.empty()){
				printf("Invalid\n");
			}
			else{
				printf("%d\n", findIndex((ss.size()+1)/2));\
			}
		}
	}

	system("pause");
	return 0;
}