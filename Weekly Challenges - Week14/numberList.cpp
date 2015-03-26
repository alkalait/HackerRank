#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> void readVector(vector<T> &v, long size);
template<typename T> T findMax(vector<T> &v, long first, long last);
template<typename T> void printVector(vector<T> &x);


int main() {
	long T;
	cin >> T;

	for (long iTest=0; iTest < T; ++iTest) {
		long N, K;
		cin >> N >> K;
		// Read vector.
		vector<long> A(N,0);
		readVector(A, N);
		//printVector(A);

		long count = 0;
		for (long windowSize = 1; windowSize <= N; ++windowSize) {
			int runningMax = findMax(A, 0, windowSize);
			if (runningMax > K) count++;
			for (long location = 1; location < N - windowSize + 1; ++location) {
				long previous = A[location - 1];
				long first    = A[location];
				long last     = A[location + windowSize - 1];
                //cout << "considering " << first << " - " << last << endl;
				if (first > runningMax || last > runningMax) runningMax = max(first, last);
				// if ( first > K || last > K ) count++;
				if (runningMax > K) count++;
			}
		}
		cout << count << endl;// << endl;
	}

	return 0;
}


template<typename T> T findMax(vector<T> &v, long first, long last)
{
	T max = 0;

	for (long i = first; i < last; ++i) {
		if (v[i] > max) max = v[i];
	}

	return max;
}

template<typename T> void readVector(vector<T> &v, long size)
{
	for (long i = 0; i < size; ++i) {
		cin >> v[i];
	}
}

template<typename T> void printVector(vector<T> &x)
{
	for (long i=0; i < x.capacity(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}