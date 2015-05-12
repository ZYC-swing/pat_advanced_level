//1014. Waiting in Line
/*
Suppose a bank has N windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. The rules for the customers to wait in line are:

The space inside the yellow line in front of each window is enough to contain a line with M customers. Hence when all the N lines are full, all the customers after (and including) the (NM+1)st one will have to wait in a line behind the yellow line.
Each customer will choose the shortest line to wait in when crossing the yellow line. If there are two or more lines with the same length, the customer will always choose the window with the smallest number.
Customer[i] will take T[i] minutes to have his/her transaction processed.
The first N customers are assumed to be served at 8:00am.
Now given the processing time of each customer, you are supposed to tell the exact time at which a customer has his/her business done.

For example, suppose that a bank has 2 windows and each window may have 2 custmers waiting inside the yellow line. There are 5 customers waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 in the morning, customer1 is served at window1 while customer2 is served at window2. Customer3 will wait in front of window1 and customer4 will wait in front of window2. Customer5 will wait behind the yellow line.

At 08:01, customer1 is done and customer5 enters the line in front of window1 since that line seems shorter now. Customer2 will leave at 08:02, customer4 at 08:06, customer3 at 08:07, and finally customer5 at 08:10.

Input

Each input file contains one test case. Each case starts with a line containing 4 positive integers: N (<=20, number of windows), M (<=10, the maximum capacity of each line inside the yellow line), K (<=1000, number of customers), and Q (<=1000, number of customer queries).

The next line contains K positive integers, which are the processing time of the K customers.

The last line contains Q positive integers, which represent the customers who are asking about the time they can have their transactions done. The customers are numbered from 1 to K.

Output

For each of the Q customers, print in one line the time at which his/her transaction is finished, in the format HH:MM where HH is in [08, 17] and MM is in [00, 59]. Note that since the bank is closed everyday after 17:00, for those customers who cannot be served before 17:00, you must output "Sorry" instead.

Sample Input
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
Sample Output
08:07
08:06
08:10
17:00
Sorry
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAX 0x0fffffff

void printDigit(int number){
	if (number<10)
	{
		cout << 0;
	}
	cout << number;
}

void print(int finishTime, int valid){
	if(!valid)
		cout << "Sorry";
	else{
		printDigit(finishTime/60+8);
		cout << ':';
		printDigit(finishTime%60);
	}
}

//返回正在处理的顾客中剩余时间最短的编号
int findMin(int *topTime,int n){
	int min = MAX;
	int index = -1;
	for(int i=0; i<n; i++){
		if(topTime[i]<min && topTime[i]>0){
			min = topTime[i];
			index = i;
		}
	}
	return index;
}

int main(int argc, char const *argv[])
{
	int n,m,k,q;
	int processTime[1000],finishTime[1000],valid[1000];//valid标记计算的结束时间超过540是否返回Sorry，为1则不返回Sorry
	int windowTime[20];
	queue<int> windows[20],wait;
	int topTime[20];

	memset(finishTime,0,sizeof(finishTime));
	memset(windowTime,0,sizeof(windowTime));
	memset(topTime,0,sizeof(topTime));
	memset(valid,1,sizeof(valid));

	cin >> n >> m >> k >> q;
	for (int i = 0; i < k; ++i)
	{
		cin >> processTime[i];
	}

	for(int i=0; i<k && i<n*m; i++){
		windows[i%n].push(i);
	}
	if(k>n*m){
		for(int i=n*m; i<k; i++){
			wait.push(i);
		}
	}
	for(int i=0; i<n && i<k; i++){
		int index = windows[i].front();
		topTime[i] = processTime[index];
	}

	int count = k;//未处理完的客户数
	int totalTime = 0;
	while(count--){
		int index = findMin(topTime, n);//即将处理好的队列号
		int costTime = topTime[index];
		totalTime += costTime;
		for(int i=0; i<n; i++){
			int number;
			if(!windows[i].empty()){
				number = windows[i].front();
				processTime[number] -= costTime;
				if(processTime[number] == 0){
					finishTime[number] = totalTime;
					windows[i].pop();
					if(!wait.empty()){
						int waitNum = wait.front();
						wait.pop();
						windows[i].push(waitNum);
					}
					if(!windows[i].empty()){
						number = windows[i].front();
						if(totalTime>=540)
							valid[number] = 0;
					}
				}
				topTime[i] = processTime[number];
			}
		}
	}

	int queryNumber;
	for (int i = 0; i < q; ++i)
	{
		cin >> queryNumber;
		print(finishTime[queryNumber-1], valid[queryNumber-1]);
		if (i!=q-1)
		{
			cout << endl;
		}
	}
	
	system("pause");
	return 0;
}

//第二次刷
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <climits>
using namespace std;

int main(){
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	vector<queue<int>> lines(n);
	queue<int> waiting;
	vector<int> processTime(k), finishTime(k, -1);
	vector<bool> served(k, 0);
	for (int i = 0; i < k; ++i){
		cin >> processTime[i];
	}
	for (int i = 0, curWindow = 0; i < k && i < m*n; curWindow = (curWindow + 1) % n, ++i){
		lines[curWindow].push(i);
	}
	for (int i = m*n; i < k; ++i){
		waiting.push(i);
	}
	int curTime = 0, deadline = 540;
	while (curTime < deadline){
		int minTime = INT_MAX;
		for (int i = 0; i < n; ++i){
			if (!lines[i].empty() && processTime[lines[i].front()] < minTime){
				minTime = processTime[lines[i].front()];
			}
		}
		curTime += minTime;
		for (int i = 0; i < n; ++i){
			if (!lines[i].empty()){
				int index = lines[i].front();
				processTime[index] -= minTime;
				served[index] = 1;
				if (processTime[index] == 0){
					finishTime[index] = curTime;
					lines[i].pop();
					if (!waiting.empty()){
						lines[i].push(waiting.front());
						waiting.pop();
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i){
		if (!lines[i].empty()){
			int index = lines[i].front();
			if (served[index]){
				finishTime[index] = curTime + processTime[index];
			}
		}
	}
	for (int i = 0, index; i < q; ++i){
		cin >> index;
		--index;
		if (finishTime[index] == -1){
			cout << "Sorry" << endl;
		}
		else{
			printf("%02d:%02d\n", finishTime[index] / 60 + 8, finishTime[index] % 60);
		}
	}
	system("pause");
	return 0;
}