#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int T, modulo;
    long long int sum3, sum5, sum15, N, n;
    long double _N;
    
    cin >> T;
    
    for (int iCase=0; iCase<T; iCase++) {
        cin >> N;
        
        sum3  = 0;
        sum5  = 0;
        sum15 = 0;
        
        /*
        for (int num=N-1; num>=3; num--) {
            if ((num % 3 == 0) || (num % 5 == 0)) {
                sum += num;
                cout << num << " " << sum << endl;
            }
        }
        */
        
        // Given a number, find the maximum multiple of 3, smaller than N.
        n = ((N-1) - ((N-1) % 3))/3; //cout << n << endl;
        sum3 = ((n*(n+1)) / 2) * 3; //cout << sum3 << endl; 
        
        // Given a number, find the maximum multiple of 3, smaller than N.
        n = ((N-1) - ((N-1) % 5))/5; //cout << n << endl;
        sum5 = ((n*(n+1)) / 2) * 5; //cout << sum5 << endl;
        
        // Remove multiples of 3 and 5 jointly.
        n = ((N-1) - ((N-1) % 15))/15; //cout << n << endl;
        sum15 = ((n*(n+1)) / 2) * 15; 
        
        cout << sum3 + sum5 - sum15 << endl;
    }
    
    return 0;
}
