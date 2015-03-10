#include <cmath>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int greaterThan(vector<int> a, vector<int> b);
int maxIndex(vector<int> &numbers, int from, int to);
template<typename T> void printVector(vector<T> &x);
void swap(int &a, int &b);


int main()
{
	int N, K;
	cin >> N >> K;

	// Read input.
	vector<int> numbers(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> numbers[i];
	}
	vector<int> newnumbers = numbers;

	int iSwap = 0;
	int iNum  = 0;
	while (iSwap < K && iNum < N) {
		// int iMax = maxIndex(numbers, iNum, N-1);
		swap(newnumbers[iNum++], newnumbers[maxIndex(numbers, iNum, N-1)]);
		if ( greaterThan(newnumbers, numbers) == 1 ) {
			iSwap++;
			numbers = newnumbers;
			//printVector(newnumbers);
		}
	}
	printVector(newnumbers);

	return 0;
}


void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int maxIndex(vector<int> &numbers, int from, int to)
{
	int max = 0;
	int maxIndex = -1;

	for (int i = from; i <= to; ++i) {
		if (numbers[i] > max) {
			max = numbers[i];
			maxIndex = i;
		}
	}

	return maxIndex;
}

// 0: a > b,  1: a < b,  2: a == b
int greaterThan(vector<int> a, vector<int> b)
{
	int order = 2;
	bool found = false;

	for (int i = 0; i < a.size() && !found; ++i) {
		if (a[i] > b[i]) {
			order = 1;
			found = true;
		}
		else if (a[i] < b[i]) {
			order = 0;
			found = true;
		}
	}

	return order;
}

template<typename T> void printVector(vector<T> &x)
{
	for (int i=0; i < x.capacity(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}