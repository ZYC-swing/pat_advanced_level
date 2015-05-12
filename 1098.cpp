//1098. Insertion or Heap Sort
/*
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;

void adjustDown(int cur, int size, vector<int> &vec){
	int index = 0, maximum = vec[cur - 1];
	if (2 * cur <= size && vec[2 * cur - 1] > maximum){
		index = 1;
		maximum = vec[2 * cur - 1];
	}
	if (2 * cur + 1 <= size && vec[2 * cur] > maximum){
		index = 2;
		maximum = vec[2 * cur];
	}
	switch (index){
	case 1:
		swap(vec[cur - 1], vec[2 * cur - 1]);
		adjustDown(2 * cur, size, vec);
		break;
	case 2:
		swap(vec[cur - 1], vec[2 * cur]);
		adjustDown(2 * cur + 1, size, vec);
		break;
	default:
		break;
	}
}

void buildHeap(vector<int> &vec){
	for (int i = n / 2; i >= 1; --i){
		adjustDown(i, n, vec);
	}
}

int main(){
	cin >> n;
	vector<int> origin(n), sorted(n);
	for (int i = 0; i < n; ++i){
		cin >> origin[i];
	}
	for (int i = 0; i < n; ++i){
		cin >> sorted[i];
	}

	//Insertion Sort
	vector<int> tmp = origin;
	for (int i = 2; i <= n; ++i){
		sort(tmp.begin(), next(tmp.begin(), i));
		if (tmp == sorted){
			cout << "Insertion Sort" << endl;
			sort(tmp.begin(), next(tmp.begin(), i + 1));
			for (int j = 0; j < n; ++j){
				if (j){
					cout << " ";
				}
				cout << tmp[j];
			}
			system("pause");
			return 0;
		}
	}

	//Heap Sort
	buildHeap(origin);
	tmp = origin;
	for (int i = n - 1; i > 0; --i){
		swap(tmp[0], tmp[i]);
		adjustDown(1, i, tmp);
		if (tmp == sorted){
			cout << "Heap Sort" << endl;
			--i;
			swap(tmp[0], tmp[i]);
			adjustDown(1, i, tmp);
			for (int j = 0; j < n; ++j){
				if (j){
					cout << " ";
				}
				cout << tmp[j];
			}
			break;
		}
	}

	system("pause");
	return 0;
}