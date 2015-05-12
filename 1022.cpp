//1022. Digital Library
/*
A Digital Library contains millions of books, stored according to their titles, authors, key words of their abstracts, publishers, and published years. Each book is assigned an unique 7-digit number as its ID. Given any query from a reader, you are supposed to output the resulting books, sorted in increasing order of their ID's.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=10000) which is the total number of books. Then N blocks follow, each contains the information of a book in 6 lines:

Line #1: the 7-digit ID number;
Line #2: the book title -- a string of no more than 80 characters;
Line #3: the author -- a string of no more than 80 characters;
Line #4: the key words -- each word is a string of no more than 10 characters without any white space, and the keywords are separated by exactly one space;
Line #5: the publisher -- a string of no more than 80 characters;
Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].
It is assumed that each book belongs to one author only, and contains no more than 5 key words; there are no more than 1000 distinct key words in total; and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer M (<=1000) which is the number of user's search queries. Then M lines follow, each in one of the formats shown below:

1: a book title
2: name of an author
3: a key word
4: name of a publisher
5: a 4-digit number representing the year
Output Specification:

For each query, first print the original query in a line, then output the resulting book ID's in increasing order, each occupying a line. If no book is found, print "Not Found" instead.

Sample Input:
3
1111111
The Testing Book
Yue Chen
test code debug sort keywords
ZUCS Print
2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4: ZUCS Print
5: 2011
3: blablabla
Sample Output:
1: The Testing Book
1111111
2222222
2: Yue Chen
1111111
3333333
3: keywords
1111111
2222222
3333333
4: ZUCS Print
1111111
5: 2011
1111111
2222222
3: blablabla
Not Found
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 10000

typedef struct{
	string id;
	string title;
	string author;
	vector<string> keywords;
	string publisher;
	string year;
}book;

bool cmp(book a, book b){
	return a.id<b.id;
}

int main(int argc, char const *argv[])
{
	int n,m;
	vector<book> books;
	string allKeyword,keyword;

	cin >> n;
	for(int i=0; i<n; i++){
		book tmpBook;
		cin >> tmpBook.id;
		getchar();
		getline(cin,tmpBook.title,'\n');
		getline(cin,tmpBook.author,'\n');
		getline(cin,allKeyword,'\n');
		int start=0;
		for(int j=0; j<=allKeyword.length(); j++){
			if(j==allKeyword.length() || allKeyword[j]==' '){
				keyword.assign(allKeyword,start,j-start);
				start = j+1;
				tmpBook.keywords.push_back(keyword);
			}
		}
		getline(cin,tmpBook.publisher,'\n');
		getline(cin,tmpBook.year,'\n');
		books.push_back(tmpBook);
	}

	sort(books.begin(),books.end(),cmp);

	cin >> m;
	getchar();
	string query,information;
	for(int i=0; i<m; i++){
		vector<book>::iterator it = books.begin();
		int cnt = 0;
		getline(cin,query,'\n');
		information.assign(query,3,query.length()-3);

		cout << query << endl;

		switch(query[0]){
		case '1':
			while(it!=books.end()){
				if((*it).title==information){
					cout << (*it).id << endl;
					cnt++;
				}
				it++;
			}
			break;
		case '2':
			while(it!=books.end()){
				if((*it).author==information){
					cout << (*it).id << endl;
					cnt++;
				}
				it++;
			}
			break;
		case '3':
			while(it!=books.end()){
				vector<string>::iterator subit = (*it).keywords.begin();
				while(subit!=(*it).keywords.end()){
					if((*subit)==information){
						cout << (*it).id << endl;
						cnt++;
						break;
					}
					subit++;
				}
				it++;
			}
			break;
		case '4':
			while(it!=books.end()){
				if((*it).publisher==information){
					cout << (*it).id << endl;
					cnt++;
				}
				it++;
			}
			break;
		case '5':
			while(it!=books.end()){
				if((*it).year==information){
					cout << (*it).id << endl;
					cnt++;
				}
				it++;
			}
			break;
		default:
			break;
		}
		if(!cnt){
			cout << "Not Found" << endl;
		}
	}

	system("pause");
	return 0;
}