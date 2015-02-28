#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "math.h"
using namespace std;


void readTestCase(int N, vector<double> &GPA, vector<vector<double>> &allAptScores);
double corr(vector<double> x, vector<double> y);
double mean(vector<double> &x);
double stdev(vector<double> &x);
vector<double> standardize(vector<double> &x);
void printVector(vector<double> &x);
void printMatrix(vector<vector<double>> &X);


int main() {
    int T, N, iBestAptitude;
    
    cin >> T;
    
    for (int iTestcase=0; iTestcase < T; iTestcase++) {
        cin >> N;
        
        vector<double> GPA(N);
        vector<double> singleAptScores(N,0);
        vector<vector<double>> allAptScores(5,singleAptScores);
        double r, rMax = 0;
        int bestAptitude;
        
        readTestCase(N, GPA, allAptScores);
        
       // printVector(GPA);
        //printMatrix(allAptScores);
        cout << endl;
        
        // Compute correlations of GPA with each aptitude's scores and choose the best one.
        for (int iAptitude=0; iAptitude<5; iAptitude++) {
            r = corr(GPA, allAptScores[iAptitude]);
            if (abs(r) > abs(rMax)) {
                rMax = r;
                iBestAptitude = iAptitude+1;
            }
            //cout << r << " " << rMax << endl;
        }
        
        cout << iBestAptitude << endl;
    }
    
    return 0;
}


// Reads the next test case from the input.
void readTestCase(int N, vector<double> &GPA, vector<vector<double>> &allAptScores)
{
    // Read GPA grades.
    for (int iStudent=0; iStudent < N; iStudent++) {
        cin >> GPA[iStudent];
    }

    // Read aptitude scores.
    for (int iAptitude=0; iAptitude < 5; iAptitude++) {
        for (int iStudent=0; iStudent < N; iStudent++) {
            cin >> allAptScores[iAptitude][iStudent];
        }
    }
}

// Computes the Pearson correlation between two vectors.
double corr(vector<double> x, vector<double> y)
{
    double correlation;
    double innerProduct = 0;
    double N = y.capacity();
    
    if (N>1) N--;
    
    // Normalize vectors.
    x = standardize(x);
    y = standardize(y);
    
    innerProduct = inner_product(x.begin(), x.end(), y.begin(), 0.0);
    
    return innerProduct / N;
}

double mean(vector<double> &x)
{
    return accumulate(x.begin(),x.end(), 0.0) / x.capacity();
}

double stdev(vector<double> &x)
{
    double mu = mean(x);
    double s  = 0.0;
    double N  = x.capacity();
    
    if (N>1) N -= 1;
    
    for (int i=0; i < x.capacity(); i++) {
        s += pow(x[i]-mu, 2);
    }
    
    return sqrt(s / N);
}

vector<double> standardize(vector<double> &x)
{
    vector<double> y(x.capacity());
    double s  = stdev(x);
    double mu = mean(x);
    
    for (int i=0; i < x.capacity(); i++) {
        y[i] = (x[i] - mu) / s;
    }
        
    //printVector(x);
    //printVector(y);
    
    return y;
}

void printVector(vector<double> &x)
{
    for (int i=0; i < x.capacity(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void printMatrix(vector<vector<double>> &X)
{
    for (int i=0; i < X.capacity(); i++) {
        printVector(X[i]);
    }
    cout << endl;
}
