#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

struct square {
    int number;
    square *next = 0;
};

template<typename T> void printVector(vector<T> x);
vector<double> readCSL(int size);
void rollDie(vector<double> &p, vector<int> &rolls);
void printBoard(square *board);
int playBoard(square *board, vector<int> &rolls);


int main() {
    int T;
    vector<double> p;
    vector<double> ladders_and_snakes;
    int numLadders, numSnakes;
    vector<vector<double> > ladders, snakes;
    square board[100];
    vector<int> rolls(1000,0);
    
    cin >> T;
    //cout << T << endl;
    
    for (int iTest=0; iTest<T; iTest++) {
        ladders.clear();
        snakes.clear();
        
        // Read input for this test case. //
        
        p = readCSL(6);
        //printVector(p);
        ladders_and_snakes = readCSL(2); 
        //printVector(ladders_and_snakes);
        numLadders = ladders_and_snakes[0];
        numSnakes  = ladders_and_snakes[1];
        for (int iLadder=0; iLadder<numLadders; iLadder++) {
            ladders.push_back(readCSL(2));
            //printVector(ladders[iLadder]);            
        }
        for (int iSnake=0; iSnake<numSnakes; iSnake++) {
            snakes.push_back(readCSL(2));
            //printVector(snakes[iSnake]);            
        }
                
        // Initialize the board. //
        
        for (int iBoard=0; iBoard<100; iBoard++) {
            board[iBoard].number = iBoard+1;
            board[iBoard].next = &board[iBoard]; // 
        }
        for (int iLadder=0; iLadder<numLadders; iLadder++) {
            board[(int)ladders[iLadder][0]-1].next = &board[(int)ladders[iLadder][1]-1];
        }
        for (int iSnake=0; iSnake<numSnakes; iSnake++) {
            board[(int)snakes[iSnake][0]-1].next = &board[(int)snakes[iSnake][1]-1];
        }
        //printBoard(board);
        
        // Play the game! //
        
        vector<int> numMoves(5000,0);
        //for (int iSim=0; iSim<5000; iSim++) {
        int iSim = 0;
        while (iSim < numMoves.size()) {
            rollDie(p,rolls);
            numMoves[iSim] = playBoard(board, rolls);
            if (numMoves[iSim] == 1000) {
                iSim--;
            }
            //cout << numMoves[iSim] << endl;
            iSim++;
        }
        //printVector(numMoves);
        cout << accumulate(numMoves.begin(), numMoves.end(), 0.0) / 5000.0 << endl;
    }
    
    //cout << "Terminating..." << endl;
    return 0;
}

int playBoard(square *board, vector<int> &rolls)
{
    int token, newToken, iRoll;

    iRoll = 0;
    token = 1;
    while (iRoll<1000 && token != 100) {  
        // Move to new square designated by die roll.
        newToken = token + rolls[iRoll];
        if (newToken <= 100) {
            token = board[newToken-1].next->number;
            //cout<<iRoll+1<<": New board number is "<<board[token-1].number << ". Roll was " << rolls[iRoll] << endl;
        }
        iRoll++;
    }
    return iRoll;
}

void printBoard(square *board)
{
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            cout << board[i*10 + j].number;
            if (board[i*10 + j].next != 0) {
                cout << "(" << board[i*10 + j].next->number << ")";
            }
            cout << " ";
        }
        cout << endl;
    }
}

// Simlulate n die rolls, biased with probabilities p.
void rollDie(vector<double> &p, vector<int> &rolls)
{
    //vector<int> rolls(n,0);
    int u; // Sample uniformly from 1 to 100.
    vector<double> cum_p(7, 0);
    
    for (int i=0; i<7; i++) {
        cum_p[i] = 100.0*accumulate(p.begin(), p.begin()+i, 0.0);
    }
    //printVector(cum_p);
    
    for (int iRoll=0; iRoll<rolls.size(); iRoll++) {
        u = rand() % 100;
        for (int i=1; i<=6; i++) {
            if ((cum_p[i-1] <= u)  &&  (u < cum_p[i])) {
                rolls[iRoll] = i;
                //break;
            }
        }
    }
    //return rolls;
}

// Reads a line of comma reparated data.
vector<double> readCSL(int size)
{
    string buffer, s;
    vector<double> data;//(size,0);
    
    cin >> buffer;
    stringstream ss(buffer);
    
    for (int i=0; i<size; i++) {
        getline( ss, s, ',' );
        data.push_back(stod(s));
    }
    
    return data;
}

template<typename T> void printVector(vector<T> x)
{
    for (int i=0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}
