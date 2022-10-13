#include <iostream>
#include <stack>

using namespace std;
typedef pair<int, int> coord;

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,-1,-1,-1,0,1,1,1};

class fish {
    public:
    coord loc;
    int dir;

    fish() {
        loc = coord(-1, -1);
        dir = -1;
    }

    fish(coord c, int d) {
        loc = c;
        dir = d;
    }
};

class smap {
    public:
    int eat;
    fish fishes[17];
    int view[4][4];
};

int main()
{
    smap task;
    int max_eat = 0;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            int num, dir;
            cin >> num >> dir;
            task.view[i][j] = num;
            task.fishes[num] = fish(coord(i,j), dir-1);
        }
    }

    //init
    fish tmp = task.fishes[task.view[0][0]];
    task.fishes[0] = fish(tmp.loc, tmp.dir);
    task.eat = task.view[0][0];
    task.fishes[task.view[0][0]].dir = -1;
    task.view[0][0] = 0; // shark. empty=-1

    stack<smap> task_stack;
    task_stack.push(task);

    while(!task_stack.empty()) {
        smap sim = task_stack.top();
        task_stack.pop();

        auto fishArr = sim.fishes;
        auto view = sim.view;
        auto eat = sim.eat;

        // cout << "------- " << eat << endl;

        // move fish
        for(int fidx=1; fidx<17; fidx++) {
            fish curFish = fishArr[fidx];
            if(curFish.dir == -1) continue;

            for(int addir=0; addir<8; addir++) {
                int newdir = curFish.dir + addir;
                newdir = newdir % 8;
                coord newloc = coord(curFish.loc.first + dx[newdir], curFish.loc.second + dy[newdir]);
                if(newloc.first < 0 || newloc.first >= 4 || newloc.second < 0 || newloc.second >= 4) continue;
                else if(view[newloc.first][newloc.second] == 0) continue;
                else
                {
                    int swapFishIdx = view[newloc.first][newloc.second];
                    view[curFish.loc.first][curFish.loc.second] = swapFishIdx;
                    // Swap fish exist
                    if(swapFishIdx > 0) {
                        fishArr[swapFishIdx].loc = curFish.loc;
                    }
                    view[newloc.first][newloc.second] = fidx;
                    fishArr[fidx].loc = newloc;
                    fishArr[fidx].dir = newdir;
                    break;
                }
            }

            // for(int i=0; i<4; i++) {
            //     for(int j=0; j<4; j++) {
            //         cout << view[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            // cout << "---" << endl;
        }

        // shark eat 
        fish shark = fishArr[0];
        bool finish_flag = true;
        for(int dist=1; dist<4; dist++) {
            coord newloc = coord(shark.loc.first + dx[shark.dir]*dist, shark.loc.second + dy[shark.dir]*dist);
            if(newloc.first < 0 || newloc.first >= 4 || newloc.second < 0 || newloc.second >= 4) continue;
            else if(view[newloc.first][newloc.second] == -1) continue;
            else
            {
                int eatidx = view[newloc.first][newloc.second];
                fish efish = fishArr[eatidx];
                smap newsim;
                newsim.eat = eat + eatidx;
                for(int i=0; i<4; i++) {
                    for(int j=0; j<4; j++) {
                        newsim.view[i][j] = view[i][j];
                    }
                }
                for(int i=0; i<17; i++) {
                    newsim.fishes[i] = fishArr[i];
                }
                newsim.fishes[eatidx].dir = -1;
                newsim.fishes[0].dir = efish.dir;
                newsim.fishes[0].loc = efish.loc;
                newsim.view[efish.loc.first][efish.loc.second] = 0;
                newsim.view[shark.loc.first][shark.loc.second] = -1;
                task_stack.push(newsim);
                finish_flag = false;
            }
        }
        if(finish_flag) {
            max_eat = max_eat > eat ? max_eat : eat;
        }
    }
    cout << max_eat << endl;
}