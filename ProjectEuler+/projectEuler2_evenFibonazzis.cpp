#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> void printVector(vector<T> x, int size);


int main()
{
    long int sum, T, N, limit;
    long int F_n;
    vector<long int> F(100000,0);
    F[0] = 0;
    F[1] = 1;
    F[2] = 1;

    cin >> T;

    for (int iTest = 0 ; iTest < T; iTest++)
    {
        cin >> N;
        
        for (int i = 3; F[i-1]<=N; i++)
        {
            limit = i-1;
            F[i]  = F[i-1] + F[i-2];
        }
        //printVector(F, limit);

        sum = 0;
        for (int i=3; i<=limit; i++) {
            if (i%3==0) sum += F[i];
        }
        
        cout << sum << endl;
    }

    return 0;
}


template<typename T> void printVector(vector<T> x, int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << x[i] << " ";
    }
    cout << endl;
}
