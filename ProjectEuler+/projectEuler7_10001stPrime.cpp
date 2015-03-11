#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPrime(int n, vector<int> &primesList);
template<typename T> void printVector(vector<T> &x);


int main() {
	int T;
	cin >> T;
	T = 1;
	vector<int> primesList(1,2);


	for (int iTest = 0; iTest < T; ++iTest) {
		int N;
		cin >> N;
		N = 10000;

		// Initialise sieve. Its purpose is for every position to point to the next prime.
		vector<int> sieve(105000, 0);
		for (int i = 2; i < sieve.size()-1; ++i) {
			sieve[i] = i+1;
		}
		//printVector(sieve);

		int prime  = 2;
		int iSieve = 2;
		for (int count=1; count <= N; count++) {
			prime = iSieve;
			//cout << endl << "Prime is " << prime << endl;
			for (int i = iSieve; i > 0; i = sieve[i]) {
				//cout << endl << "Moving on to " << i << endl;
				//cout << "Checking " << sieve[i] << endl;
				if (sieve[i] % prime == 0) {
					//cout << sieve[i] << " not prime" << endl;
					int pointTo = sieve[sieve[i]];
					sieve[sieve[i]] = 0;
					sieve[i] = pointTo;
					//cout << i << " now points to " << sieve[i] << endl;
				}
			}
			iSieve = sieve[ iSieve ];
			//printVector(sieve); //cout << endl;
		}
		cout << prime << endl;
	}
	return 0;
}


bool isPrime(int n, vector<int> &primesList)
{
	bool isprime = true;

	double bound = ceil(sqrt((double)n));
	for (int i = 0; i < primesList.size() && primesList[i] <= bound; ++i) {
		if (n % primesList[i] == 0) isprime = false;
	}

	if ( isprime  &&  primesList[primesList.size()-1] < n ) {
		primesList.push_back(n);
	}

	// for (int i = 2; i <= bound && isprime; ++i) {
	// 	if (n % i == 0 && n > 2) isprime = false;
	// }

	return isprime;
}

template<typename T> void printVector(vector<T> &x)
{
	for (int i=0; i < x.capacity(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}