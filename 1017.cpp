//1017. Queueing at Bank
/*
Suppose a bank has K windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. All the customers have to wait in line behind the yellow line, until it is his/her turn to be served and there is a window available. It is assumed that no window can be occupied by a single customer for more than 1 hour.

Now given the arriving time T and the processing time P of each customer, you are supposed to tell the average waiting time of all the customers.

Input Specification:

Each input file contains one test case. For each case, the first line contains 2 numbers: N (<=10000) - the total number of customers, and K (<=100) - the number of windows. Then N lines follow, each contains 2 times: HH:MM:SS - the arriving time, and P - the processing time in minutes of a customer. Here HH is in the range [00, 23], MM and SS are both in [00, 59]. It is assumed that no two customers arrives at the same time.

Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will have to wait in line till 08:00, and anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.

Output Specification:

For each test case, print in one line the average waiting time of all the customers, in minutes and accurate up to 1 decimal place.

Sample Input:
7 3
07:55:00 16
17:00:01 2
07:59:59 15
08:01:00 60
08:00:00 30
08:00:02 2
08:03:00 10
Sample Output:
8.2
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef struct{
  int arriveTime;
  int processTime;
  int startTime;
  int waitTime;
}customer;

bool cmp(customer c1, customer c2){
  return c1.arriveTime<c2.arriveTime;
}

int main(int argc, char const *argv[])
{
  queue<customer> windows[100];
  vector<customer> customers;
  customer tmp;
  int start,deadline;
  int n,k,validCnt;
  string arriveTime;
  int processTime;

  start = 8*3600;
  deadline = 17*3600;

  validCnt=0;
  cin >> n >> k;
  for(int i = 0; i < n; ++i){
    cin >> arriveTime >> processTime;
    tmp.arriveTime = ((arriveTime[0]-'0')*10+arriveTime[1]-'0')*3600
            +((arriveTime[3]-'0')*10+arriveTime[4]-'0')*60
            +(arriveTime[6]-'0')*10+arriveTime[7]-'0';
    tmp.processTime = processTime*60;
    tmp.waitTime = 0;
    if(tmp.arriveTime<=deadline){
      validCnt++;
      customers.push_back(tmp);
    }
  }

  sort(customers.begin(), customers.end(), cmp);
  int currentTime = start;
  float totalWait = 0.0;

  vector<customer>::iterator it = customers.begin();
  while(it!=customers.end()){
    int min = 3601;
    int nullTime = 3601;//柜台空等时间
    for(int i=0; i<k; i++){
      if(!windows[i].empty()){
        if(windows[i].front().processTime<min){
          min = windows[i].front().processTime;
        }
      }
      else if(it!=customers.end()){
        if((*it).arriveTime<=currentTime){
          (*it).startTime = currentTime;
          (*it).waitTime = (*it).startTime-(*it).arriveTime;
          totalWait += (*it).waitTime;
          windows[i].push(*it);
          it++;
          if(windows[i].front().processTime<min){
            min = windows[i].front().processTime;
          }
        }
        else if((*it).arriveTime-currentTime<min){
          min = (*it).arriveTime-currentTime;
        }
      }
      else
        break;
    }

    currentTime += min;
    for(int i=0; i<k; i++){
      if(!windows[i].empty()){
        windows[i].front().processTime -= min;
        if(windows[i].front().processTime==0){
          windows[i].pop();
        }
      }
    }
  }

  if(validCnt==0){
    totalWait = 0.0;
  }
  else{
    totalWait = totalWait/validCnt;
  }
  totalWait /= 60;
  printf("%.1f", totalWait);

  customers.clear();
  system("pause");
  return 0;
}

//第二次刷
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cstdint>
#include <cmath>
using namespace std;

struct customer{
  int arriveTime;
  int startTime;
  int processTime;
};

bool cmp(customer c1, customer c2){
  return c1.arriveTime < c2.arriveTime;
}

int main(){
  int n, k;
  cin >> n >> k;
  vector<customer> customers(n), windows(k);
  vector<bool> empty(k, 1);
  queue<customer> qq;
  for (int i = 0; i < n; ++i){
    int hh, mm, ss;
    scanf("%d:%d:%d %d", &hh, &mm, &ss, &customers[i].processTime);
    customers[i].processTime *= 60;
    customers[i].arriveTime = hh * 3600 + mm * 60 + ss;
  }
  sort(customers.begin(), customers.end(), cmp);
  int curTime = 8 * 3600;
  int deadLine = 17 * 3600;
  int validCnt = 0;
  while (validCnt < n){
    if (customers[validCnt].arriveTime > deadLine){
      break;
    }
    qq.push(customers[validCnt++]);
  }
  customers.clear();
  int sum = 0, cnt = 0;
  while (cnt < validCnt){
    int minStep = INT_MAX;
    for (int i = 0; i < k; ++i){
      if (empty[i]){
        if (qq.empty()){
          continue;
        }
        else if (qq.front().arriveTime > curTime){
          minStep = min(minStep, qq.front().arriveTime - curTime);
          continue;
        }
        empty[i] = 0;
        windows[i] = qq.front();
        qq.pop();
        sum += curTime - windows[i].arriveTime;
        ++cnt;
        minStep = min(minStep, windows[i].processTime);
      }
      else{
        minStep = min(minStep, windows[i].processTime);
      }
    }
    for (int i = 0; i < k; ++i){
      if (!empty[i]){
        windows[i].processTime -= minStep;
        if (windows[i].processTime == 0){
          empty[i] = 1;
        }
      }
    }
    curTime += minStep;
  }
  cout << fixed << setprecision(1) << sum * 1.0 / (60 * validCnt);

  system("pause");
  return 0;
}