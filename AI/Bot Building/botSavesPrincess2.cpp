#include <iostream>
#include <vector>
using namespace std;

void nextMove(int n, int r, int c, vector <string> grid){
    size_t index;
    int princess_r, princess_c;
    string move;
    
    //Find princess position.
    for(int i=0; i<n; i++) {
        index = grid[i].find("p");
        if (index != string::npos) {
            princess_r = i;
            princess_c = index;
        } 
    }
    
    if (princess_r > r) move = "DOWN";
    else if (princess_r < r) move = "UP";
        
    if (princess_c > c) move = "RIGHT";
    else if (princess_c < c) move = "LEFT";
        
    cout << move << endl;    
}

int main(void) {

    int n, r, c;
    vector <string> grid;

    cin >> n;
    cin >> r;
    cin >> c;

    for(int i=0; i<n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    nextMove(n, r, c, grid);
    return 0;
}
