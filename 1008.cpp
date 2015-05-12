//1008.Elevator
/*
The highest building in our city has only one elevator. A request list is made up with N positive numbers. The numbers denote at which floors the elevator will stop, in specified order. It costs 6 seconds to move the elevator up one floor, and 4 seconds to move down one floor. The elevator will stay for 5 seconds at each stop.

For a given request list, you are to compute the total time spent to fulfill the requests on the list. The elevator is on the 0th floor at the beginning and does not have to return to the ground floor when the requests are fulfilled.

Input Specification:

Each input file contains one test case. Each case contains a positive integer N, followed by N positive numbers. All the numbers in the input are less than 100.

Output Specification:

For each test case, print the total time on a single line.

Sample Input:
3 2 3 1
Sample Output:
41
*/
#include <iostream>
using namespace std;

int main(){
	int n, pre, next;
	int sum;

	cin >> n;
	sum = 5*n;
	pre = 0;
	while(n--){
		cin >> next;
		if(next > pre)
			sum += 6*(next-pre);
		else
			sum += 4*(pre-next);
	}

	cout << sum;

	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
using namespace std;

int main(){
	int n, sum, pre = 0, next;
	cin >> n;
	sum = 5 * n;
	while(n--){
		cin >> next;
		sum += next > pre ? 6 * (next - pre) : 4 * (pre - next);
		pre = next;
	}
	cout << sum;
	return 0;
}