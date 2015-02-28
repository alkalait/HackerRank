#include <iostream>
#include <vector>
using namespace std;


void displayPathtoPrincess(int n, vector <string> grid){
    size_t index;
    int bot_r = ((n+1)/2)-1, bot_c = ((n+1)/2)-1;
    int pri_r, pri_c;
    string move;
    
    for(int i=0; i<n; i++) {
        //Find bot position.
        index = grid[i].find("p");
        if (index != string::npos) {
            pri_r = i;
            pri_c = index;
        }
    }
       
    while ((pri_r != bot_r) || (pri_c != bot_c)) {
        if (pri_r > bot_r) {  
            move = "DOWN";
            bot_r++;
        }
        else if (pri_r < bot_r) {
            move = "UP";
            bot_r--;
        }
        cout << move << endl;

        if (pri_c > bot_c) {
            move = "RIGHT";
            bot_c++;
        }
        else if (pri_c < bot_c) {
            move = "LEFT";
            bot_c--;
        }
        cout << move << endl;
    }
}

int main(void) {

    int m;
    vector <string> grid;

    cin >> m;
    //m = 3;

    for(int i=0; i<m; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }
    //grid.push_back("--p");
    //grid.push_back("-m-");
    //grid.push_back("---");
    

    displayPathtoPrincess(m,grid);
    //cout << "RIGHT" << endl << "DOWN" << endl << "LEFT" << endl << "LEFT" << endl;
    //cout << "UP\nUP\nRIGHT\nRIGHT" << endl;
    
    return 0;
}
