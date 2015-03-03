#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void readMatrix(vector<vector<double>> &X);
double corr(vector<double> x, vector<double> y);
vector<vector<double> > corr(vector<vector<double> > &X);
vector<vector<double> > transpose(vector<vector<double> > &X);
double mean(vector<double> &x);
double stdev(vector<double> &x);
vector<double> standardize(vector<double> &x);
void printVector(vector<double> &x);
void printMatrix(vector<vector<double> > X);


int main()
{
    int N;
    cin >> N;
    vector<vector<double> > allScores(N, vector<double> (3,0.0)); // Nx3 matrix.
    vector<vector<double> > correlationMatrix(3, vector<double> (3,0.0)); // 3x3 matrix.

    readMatrix(allScores);

    correlationMatrix = corr(allScores);
    //printMatrix(correlationMatrix);

    printf("%.2f\n", correlationMatrix[1][0]);
    printf("%.2f\n", correlationMatrix[2][1]);
    printf("%.2f\n", correlationMatrix[2][0]);

    return 0;
}


// Computes the correlation matrix from a data matrix X, of size columns x columns.
vector<vector<double> > corr(vector<vector<double> > &X)
{
    int columns = X[0].capacity();
    vector<vector<double> > corrMatrix(columns, vector<double> (columns, 0.0));
    vector<vector<double> > X_transpose = transpose(X);

    // Compute the lower-triangle of the correlation matrix.
    for ( int i = 0; i < columns; i++ ) {
        for ( int j = 0; j <= i; j++ ) {
            corrMatrix[i][j] = corr(X_transpose[i], X_transpose[j]);
            // Copy the computed element over to the upper-triangle.
            if (i != j) corrMatrix[j][i] = corrMatrix[i][j];
        }
    }

    return corrMatrix;
}

// Returns the transpose of matrix X.
vector<vector<double> > transpose(vector<vector<double> > &X)
{
    int rows    = X.capacity();
    int columns = X[0].capacity();

    vector<double> _row(rows, 0); // This becomes as long as a column of the original matrix.
    vector<vector<double> > transposedMatrix(columns, _row);

    for (int j = 0; j < columns; j++) {
        // Fill in _row.
        for (int i=0; i<rows; i++) {
            _row[i] = X[i][j];
        }
        // Copy it into the transposed matrix.
        transposedMatrix[j] = _row;
    }

    return transposedMatrix;
}

// Computes the Pearson correlation between vectors x and y.
double corr(vector<double> x, vector<double> y)
{
    double correlation;
    double innerProduct = 0.0;
    double N = y.capacity();

    if (N>1) N--;

    // Normalize vectors.
    x = standardize(x);
    y = standardize(y);

    innerProduct = inner_product(x.begin(), x.end(), y.begin(), 0.0);

    return innerProduct / N;
}

// Computes the mean of the elements in vector x.
double mean(vector<double> &x)
{
    return accumulate(x.begin(),x.end(), 0.0) / x.capacity();
}

// Computes the standard deviation of the elements in vector x.
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

// Standardizes the elements in vector x, to mean 0 and std. deviation 1.
vector<double> standardize(vector<double> &x)
{
    vector<double> y(x.capacity());
    double s  = stdev(x);
    double mu = mean(x);

    for (int i=0; i < x.capacity(); i++) {
        y[i] = (x[i] - mu) / s;
    }

    return y;
}

void readMatrix(vector<vector<double> > &X)
{
    int rows    = X.capacity();
    int columns = X[0].capacity();

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            cin >> X[i][j];
        }
    }
}

void printVector(vector<double> &x)
{
    for (int i=0; i < x.capacity(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void printMatrix(vector<vector<double> > X)
{
    for (int i=0; i < X.capacity(); i++) {
        printVector(X[i]);
    }
    cout << endl;
}


