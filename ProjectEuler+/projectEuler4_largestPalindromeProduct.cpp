#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {

	int T, N;
	cin >> T;
	// T=1;

	for (int iCase = 0; iCase < T; ++iCase)
	{
		cin >> N;
		// N = 800000;//101110;
		bool found = false;
		int maxPalindrome = 999999, candidatePalindrome;// targetPalindrome = 0;
		int max_d1, max_d2, max_d3;

		// Find largest maxPalindrome number.
		for (int d = 999; d>=100 && maxPalindrome >= N; d--) {
			int d1 = d/100, d2 = (d%100)/10, d3 = ((d%100)%10);
			candidatePalindrome = 100001*d1 + 10010*d2 + 1100*d3;
			maxPalindrome = 100001*d1 + 10010*d2 + 1100*d3;
			max_d1 = d1; max_d2 = d2; max_d3 = d3;
		}
		candidatePalindrome = maxPalindrome;

		// Find largest palindrome product.
        for (int d = max_d1*100+max_d2*10+max_d3; (d>=100 && !found); d--) {
        	int d1 = d/100, d2 = (d%100)/10, d3 = ((d%100)%10);
        	candidatePalindrome = 100001*d1 + 10010*d2 + 1100*d3;
        	//cout << d1<< " " <<d2<< " " <<d3 << " = " <<candidatePalindrome << endl;
        	for (int p1 = 100; p1 <= sqrt(candidatePalindrome); p1++) {
        		for (int p2 = max(p1, candidatePalindrome/p1 - 1); p2 <= min(candidatePalindrome/p1+1,999); p2++) {
        			//cout << p1 <<"*"<< p2 <<" = "<< p1*p2 << endl;
        			if (candidatePalindrome == p1*p2) {
        				found = true;
        			}
        		}
        	}
        }
        cout << candidatePalindrome << endl;
    }

    return 0;
}
