#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> loc;

class fish {
    public:

    loc location;
    int distance;

    fish() {
        location = loc(-1, -1);
        distance = -1;
    }

    fish(loc loc, int dist) {
        location = loc;
        distance = dist;
    }

};

int ix[4] = {1, 0, -1, 0};
int iy[4] = {0, 1, 0, -1};

int main()
{
    int N;
    cin >> N;
    int fish_map[20][20];
    int move_map[20][20];
    int seat = 0;
    int ssize = 2;
    int ssecond = 0;
    loc sloc;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> fish_map[i][j];
            if(fish_map[i][j] == 9)  {sloc = loc(i, j); fish_map[i][j] = 0;}
            move_map[i][j] = 0;
        }
    }

    queue<fish> task;
    vector<fish> eatables;

    while(true) {

        eatables.clear();
        task.push(fish(sloc, 0));
        move_map[sloc.first][sloc.second] = -1;
        int min_fish_dist = 0x7fffffff;

        // BFS
        while(!task.empty()) {

            fish tmp = task.front();
            task.pop();

            if(fish_map[tmp.location.first][tmp.location.second] > 0 && fish_map[tmp.location.first][tmp.location.second] < ssize) {
                if(tmp.distance < min_fish_dist) {
                    eatables.clear();
                    eatables.push_back(fish(tmp));
                    min_fish_dist = tmp.distance;
                }
                if(tmp.distance == min_fish_dist) {
                    eatables.push_back(fish(tmp));
                }
            }

            for(int i=0; i<4; i++) {
                loc newloc = loc(tmp.location.first + ix[i], tmp.location.second+ iy[i]);
                if(newloc.first < 0 || newloc.first >= N || newloc.second < 0 || newloc.second >= N) continue;
                if(move_map[newloc.first][newloc.second] == -1) continue;
                if(fish_map[newloc.first][newloc.second] > ssize) continue;
                task.push(fish(newloc, tmp.distance+1));
                move_map[newloc.first][newloc.second] = -1;
            }
        }

        for(int i=0; i<20; i++) {
            for(int j=0; j<20; j++) {
                move_map[i][j] = 0;
            }
        }


        // eat
        int minx = 0x7fffffff;
        int miny = 0xffffffff;

        if(eatables.empty()) {
            break;
        }


        for(int i=0; i<eatables.size(); i++) {
            fish tmp = eatables.at(i);

            if(tmp.location.first < minx) {
                miny = tmp.location.second;
                minx = tmp.location.first;
            }
            else if(tmp.location.first == minx && tmp.location.second < miny) {
                miny = tmp.location.second;
                minx = tmp.location.first;
            }
        }


        seat += 1;
        fish_map[minx][miny] = 0;
        sloc = loc(minx, miny);
        ssecond += min_fish_dist;
        if(seat == ssize) {
            ssize += 1;
            seat = 0;
        }
    }
    
    cout << ssecond << endl;
}