#include<iostream>
#include<vector>
using namespace std;


void nextMove(int r, int c, vector <string> grid){
    size_t index;
    int dirt_r, dirt_c;//, dirtIndex;
    //vector<vector<int> > allDirt;
    //findAllDirt(grid, allDirt);
    //vector<vector<int> > relative(allDirt.size(), vector<int> (2,0));
    //vector<int> dirt_pos(2,0);
    string move;
        
    //Find dirt position, searching row-first.
    for(int i=0; i<5; i++) {
        index = grid[i].find("d");
        if (index != string::npos) {
            dirt_r = i;
            dirt_c = index;
            break;
        }
    }
    
    if (dirt_r > r) move = "DOWN";
    else if (dirt_r < r) move = "UP";
    else if (dirt_c > c) move = "RIGHT";
    else if (dirt_c < c) move = "LEFT";
    else move = "CLEAN"; 
        
    cout << move << endl;    
}



int main(void) {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;
        cin >> s;
        board.push_back(s);
    }
    nextMove(pos[0], pos[1], board);
    return 0;
}
