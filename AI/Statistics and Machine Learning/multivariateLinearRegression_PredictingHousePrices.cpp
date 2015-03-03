#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename T> vector<vector<T> > submatrix(vector<vector<T> > X, int i1, int i2, int j1, int j2);
void readMatrix(vector<vector<double> > &X);
//double corr(vector<double> x, vector<double> y);
//vector<vector<double> > corr(vector<vector<double> > &X);
vector<vector<double> > transpose(vector<vector<double> > &X);
//double mean(vector<double> &x);
//double stdev(vector<double> &x);
//vector<double> standardize(vector<double> &x);
void printVector(vector<double> &x);
void printMatrix(vector<vector<double> > X);
template<typename T> vector<T> solve(vector<vector<T> > A, vector<T> b);
template<typename T> vector<T> solve(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<T> multiply(vector<vector<T> > A, vector<T> b);
template<typename T> vector<vector<T> > multiply(vector<vector<T> > A, vector<vector<T> > B);
template<typename T> vector<T> vec(vector<vector<T> > X);


int main() {

    int F, N, T;

    cin >> F >> N;

    vector<vector<double> > data(N, vector<double> (F+1, 0.0)); // N x (F+1) matrix.

    // Read training data.
    readMatrix(data);
    //printMatrix(data);

    vector<vector<double> > X   = submatrix(data, 0, N-1, 0, F-1);
    vector<vector<double> > X_t = transpose(X);
    X_t.resize(F+1);
    X_t[F] = vector<double> (N,1);
    X = transpose(X_t);
    vector<double> y = vec(submatrix(data, 0, N-1, F, F));
    //printMatrix(X); printVector(y);

    //
    vector<vector<double> > Xt_X = multiply(X_t, X);
    vector<double>          Xt_y = multiply(X_t, y);
    vector<double>             w = solve(Xt_X , Xt_y);
    //printVector(w);

    // Read test data.
    cin >> T;
    vector<vector<double> > test(T, vector<double> (F, 0.0)); // T x F matrix.
    readMatrix(test);
    vector<vector<double> > test_t = transpose(test);
    test_t.resize(F+1);
    test_t[F] = vector<double> (T,1);
    test = transpose(test_t);
    //printMatrix(test);
    vector<double> y_test = multiply(test, w);

    for (int i = 0; i < y_test.size(); ++i) {
        cout << y_test[i] << endl;
    }
    //

    return 0;
}



// Returns the transpose of matrix X.
vector<vector<double> > transpose(vector<vector<double> > &X)
{
    int rows    = X.size();
    int columns = X[0].size();

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



void readMatrix(vector<vector<double> > &X)
{
    int rows    = X.size();
    int columns = X[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
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

template<typename T> vector<vector<T> > submatrix(vector<vector<T> > X, int i1, int i2, int j1, int j2)
{
    int rows = i2 - i1 + 1;
    int cols = j2 - j1 + 1;
    vector<vector<T> > sub(rows, vector<T> (cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sub[i][j] = X[ i1 + i ][ j1 + j ];
        }
    }

    return sub;
}

template<typename T> vector<T> solve(vector<vector<T> > A, vector<T> b)
{
    int size = A.size();
    vector<T> x = b;

    // Eliminate lower-triangular part.
    for (int p = 0; p < size; p++) { // Current pivot.
        // Normalise row.
        double coeff = A[p][p];
        for (int j = p; j < size; j++) {
            A[p][j] /= coeff;
        }
        b[p] /= coeff;
        //printMatrix(A); printVector(b); cout << endl;

        for (int i = p+1; i < size; ++i) {  // Variable to eliminate.
            double coeff = A[i][p] / A[p][p];
            //cout << coeff << endl;
            for (int k = p; k < size; k++) { //
                A[i][k] -= A[p][k] * coeff;
            }
            b[i] -= b[p] * coeff;
            //printMatrix(A); printVector(b); cout << endl;
        }
    }

    // Eliminate upper-triangular part.
    for (int p = size-1; p >= 0; p--) {
        for (int i = p-1; i >= 0; i--) {
            double coeff = A[i][p] / A[p][p];
            A[i][p] -= A[p][p] * coeff;
            b[i]    -= b[p] * coeff;
            //printMatrix(A); printVector(b); cout << endl;
        }
    }

    return b;
}

template<typename T> vector<T> solve(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<T> x;
    if (B.size() == 1) {
        x = solve(A, B[0]);
    }
    return x;
}

template<typename T> vector<T> multiply(vector<vector<T> > A, vector<T> b)
{
    vector<T> product(A.size(), 0.0);

    for (int i = 0; i < A.size(); ++i) {
        product[i] = inner_product(A[i].begin(), A[i].end(), b.begin(), 0.0);
    }

    return product;
}

template<typename T> vector<vector<T> > multiply(vector<vector<T> > A, vector<vector<T> > B)
{
    vector<vector<T> > B_transpose = transpose(B);
    vector<vector<T> > product_transpose(B[0].size(), vector<T> (A.size(), 0.0));

    for (int j = 0; j < B[0].size(); ++j) {
        product_transpose[j] = multiply(A, B_transpose[j]);
    }
    return transpose( product_transpose );
}

template<typename T> vector<T> vec(vector<vector<T> > X)
{
    int rows = X.size();
    int cols = X[0].size();
    vector<T> v(rows*cols, 0.0);

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            v[j*rows + i] = X[i][j];
        }
    }

    return v;
}
