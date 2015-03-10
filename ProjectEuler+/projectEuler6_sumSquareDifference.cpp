#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; ++i) {
    	int N;
    	cin >> N;

    	long long sum = 0;
    	for (int j = 1; j <= N; ++j) {
    		sum += pow(j,2)*(j-1);
    	}
    	cout << sum << endl;
	}

	return 0;
}
