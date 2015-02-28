#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {

	long T, N;

	cin >> T;

	for (int iTest = 0; iTest < T; ++iTest) {
		cin >> N;
        
        long sqrtN     = ceil(sqrt(N));
		long remaining = N, N2 = N;
        		
        for (long factor=2; factor<=sqrtN; factor++) {
			while (N2 % factor == 0 && N2 != factor) {
				N2 /= factor;
				remaining = N2;
			}
		}
		cout << remaining << endl;
	}
	return 0;
}