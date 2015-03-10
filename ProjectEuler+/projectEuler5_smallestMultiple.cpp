#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    int T;
    cin >> T;

    for (int iTest=0; iTest<T; ++iTest) {
        int N;
        cin >> N;

        int product = 1;
        for (int iPrime=0; primes[iPrime] <= N; ++iPrime) {
            //cout << "Considering prime " << primes[iPrime] << endl;
            //cout << "Used at power " << floor(log(N)/log(primes[iPrime])) << endl;
            product *= pow( primes[iPrime], floor(log(N)/log(primes[iPrime])) );
        }
        cout << product << endl;
    }

    return 0;
}
