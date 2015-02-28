#include<iostream>
#include<vector>
using namespace std;

void findAllDirt(vector<string> grid, vector<vector<int> > &allDirt)
{
    size_t index;
    //vector<vector<int> > allDirt;
    vector<int> dirt_pos(2,0);
    
    //Find all dirt.
    for(int i=0; i<grid.size(); i++) {
        index = 0;
        while (index != string::npos){
            index = grid[i].find("d", index+1);
            if (index != string::npos) {
                dirt_pos[0] = i;
                dirt_pos[1] = index;
                allDirt.push_back(dirt_pos);
            }
        }
    }
    
    //return allDirt;
}

int relativeDirtPosition(int r, int c, vector<vector<int> > allDirt, vector<vector<int> > &relative)
{
    //vector<vector<int> > relative(allDirt.size(), vector<int> (2,0));
    int dirtIndex;
    int L1Dist, minL1Dist = 8;
    
    for (int i=0; i<allDirt.size(); i++) {
        relative[i] = { (r-allDirt[i][0]), (c-allDirt[i][1]) };
        L1Dist = abs(relative[i][0]) + abs(relative[i][1]);
        if ( L1Dist < minL1Dist ) {
            minL1Dist = L1Dist;
            dirtIndex = i;
        }
    }
    
    return dirtIndex;
}

void next_move(int r, int c, vector <string> grid){
    size_t index;
    int dirt_r, dirt_c, dirtIndex, dist, minDist = 9;
    vector<vector<int> > allDirt;
    findAllDirt(grid, allDirt);
    vector<vector<int> > relative(allDirt.size(), vector<int> (2,0));
    vector<int> dirt_pos(2,0);
    string move;
    
    int min_r, min_c;
    
    //
    //Find dirt position, searching row-first.
    for(int i=0; i<5; i++) {
        index = grid[i].find("d");
        if (index != string::npos) {
            //dirt_r = i;
            //dirt_c = index;
            dist   = abs(r-i) + abs(c-(int)index);
            if (dist < minDist) {
                minDist = dist;
                dirt_r = i;
                dirt_c = index;
            }
            //break;
        }
    }
    //
    
    /*
    dirtIndex = relativeDirtPosition(r, c, allDirt, relative);
    dirt_r = allDirt[dirtIndex][0];
    dirt_c = allDirt[dirtIndex][1];
    */
    
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
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
    return 0;
}
