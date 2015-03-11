#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//bool isPrime(int n, vector<int> &primesList);
template<typename T> void printVector(vector<T> &x);


int main() {
	int T;
	cin >> T;
	T = 1;
	vector<int> primesList(10000,0);

	// Initialise sieve. Its purpose is for every position to point to the next prime.
	vector<int> sieve(105000, 0);
	for (int i = 2; i < sieve.size()-1; ++i) {
		sieve[i] = i+1;
	}
	//printVector(sieve);

	// Build the sieve.
	int iSieve = 2;
	for (int count=1; count <= 10000; count++) {
		int prime = iSieve;
		for (int i = iSieve; i > 0; i = sieve[i]) {
			if (sieve[i] % prime == 0) {
				int pointTo = sieve[sieve[i]];
				sieve[sieve[i]] = 0;
				sieve[i] = pointTo;
			}
		}
		iSieve = sieve[ iSieve ];
		primesList[count-1] = prime;
	}

	for (int iTest = 0; iTest < T; ++iTest) {
		int N;
		cin >> N;
		N = 10000;
		cout << primesList[N-1] << endl;
	}
	return 0;
}


/*bool isPrime(int n, vector<int> &primesList)
{
	bool isprime = true;

	double bound = ceil(sqrt((double)n));
	for (int i = 0; i < primesList.size() && primesList[i] <= bound; ++i) {
		if (n % primesList[i] == 0) isprime = false;
	}

	if ( isprime  &&  primesList[primesList.size()-1] < n ) {
		primesList.push_back(n);
	}

	return isprime;
}*/

template<typename T> void printVector(vector<T> &x)
{
	for (int i=0; i < x.capacity(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}