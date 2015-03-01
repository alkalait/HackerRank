#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <numeric>      // std::accumulate
#include <algorithm>
using namespace std;


vector<int> readCoordinates(int d);
template<typename T> void printVector(vector<T> &x);
//template<typename T> void printMatrix(vector<vector<T> > &X);
int computeCityToMarketDistance(vector<int> &cityCoordinates, vector<int> &marketCoordinates, int threshold);
vector<int> incrementCoordinates(vector<int> coordinates, int base);
vector<vector<int> > generateCityCoordinates(int length, int dimension);
int updateMinimumDistances(vector<vector<int> > &cityCoordinates, vector<int> &minimumDistances, vector<int> &marketCoordinates);


int main()
{
	// Hypercube size, dimension, number of markets.
	int T, N, d, K;

	cin >> T;

	for (int iTest = 0; iTest < T; ++iTest)
	{
		cin >> N >> d >> K;
			//cout << N << " " << d << " " << K << endl << endl;

		int numCities = pow( N, d );
		//vector<vector<int> > marketCoordinates(K, vector<int> (d,0));
		vector<int> marketCoordinates(d, 0);
		vector<vector<int> > cityCoordinates = generateCityCoordinates(N, d);
			//printMatrix(cityCoordinates);
		vector<int> minimumDistances(numCities, (N-1)*d);
			//printVector(minimumDistances); cout << endl;

		for (int k = 0; k < K; ++k) {
			/* Read markets' coordinates. */
			marketCoordinates = readCoordinates(d);  //printVector( marketCoordinates[k] );
			/* Update distances. */
			int sum = updateMinimumDistances(cityCoordinates, minimumDistances, marketCoordinates); //printVector(minimumDistances);
			//cout << accumulate(minimumDistances.begin(), minimumDistances.end(), 0) << endl;
			cout << sum << endl;
		}
	}

	return 0;
}


int updateMinimumDistances(vector<vector<int> > &cityCoordinates, vector<int> &minimumDistances, vector<int> &marketCoordinates)
{
	int sum = 0;
	for (int iCity = 0; iCity < cityCoordinates.size(); ++iCity)
	{
		//printVector(minimumDistances);
		int distance = computeCityToMarketDistance(cityCoordinates[iCity], marketCoordinates, minimumDistances[iCity]);
		if ( distance < minimumDistances[iCity] ) {
			minimumDistances[iCity] = distance;
		}
		if (distance == 0) {
			cityCoordinates[iCity]  = cityCoordinates.back(); 	cityCoordinates.pop_back();
			minimumDistances[iCity] = minimumDistances.back();	minimumDistances.pop_back();
			iCity--;
		}
		else {
			sum += minimumDistances[iCity];
		}
		//printVector(minimumDistances);
	}
	return sum;
}


int computeCityToMarketDistance(vector<int> &cityCoordinates, vector<int> &marketCoordinates, int threshold)
{
	int distance = 0;

	for (int i = 0; distance < threshold  &&  i < cityCoordinates.size(); ++i) {
		distance += abs( cityCoordinates[i] - marketCoordinates[i] );
	}

	return distance;
}


vector<vector<int> > generateCityCoordinates(int length, int dimension)
{
	int numCities = pow( length, dimension );
	vector<vector<int> > cityCoordinates(numCities, vector<int> (dimension, 1));

	// cityCoordinates.push_back(vector<int> (dimension, 1));
	for (int iCity = 1; iCity < numCities; ++iCity) {
		cityCoordinates[iCity] = incrementCoordinates(cityCoordinates[iCity-1], length);
	}
	return cityCoordinates;
}

vector<int> incrementCoordinates(vector<int> coordinates, int base)
{
	int dimension = coordinates.size();
	vector<int> newCoordinates = coordinates;
	bool carry = true;

	for (int iCoord = dimension-1; iCoord >= 0 && carry; iCoord--)
	{
		if (newCoordinates[iCoord] < base) {
			newCoordinates[iCoord] += carry;
			carry = false;
		}
		else {
			newCoordinates[iCoord] = 1;
			carry = true;
		}
	}
	return newCoordinates;
}


vector<int> readCoordinates(int d)
{
	std::vector<int> coordinates(d,0);

	for (int iDim = 0; iDim < d; ++iDim)
	{
		cin >> coordinates[iDim];
	}

	return coordinates;
}

template<typename T> void printVector(vector<T> &x)
{
	for (int i = 0; i < x.size(); ++i)
	{
		cout << x[i] << " ";
	}
	cout << endl;
}


template<typename T> void printMatrix(vector<vector<T> > &X)
{
	for (int i = 0; i < X.size(); ++i)
	{
		printVector( X[i] );
	}
	cout << endl;
}
