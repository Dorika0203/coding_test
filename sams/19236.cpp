#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// typedef pair<int, int> fish;  // num, dir
// typedef pair<int, int> coord; // x, y

class fish {
    public:
    int num;
    int dir;

    fish() {
        num = -1;
        dir = -1;
    }
    fish(int n, int d) {
        num = n;
        dir = d;
    }
};

class coord {
    public:
    int x, y;
    coord() {
        x = y = -1;
    }
    coord(int _x, int _y) {
        x = _x;
        y = _y;
    }
};


class simulation_map
{
public:
    int eat;
    fish view[4][4];
    coord fishes[17];
};

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int main()
{

    simulation_map task;
    int eat_max = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int num, dir;
            cin >> num >> dir;
            task.view[i][j] = fish(num, dir - 1);
            task.fishes[num] = coord(i, j);
        }
    }

    // init. shark number is 0.
    task.eat += task.view[0][0].num;
    task.fishes[task.view[0][0].num] = coord(-1, -1);
    task.fishes[0] = coord(0, 0);
    task.view[0][0].num = 0;

    stack<simulation_map> task_stack;
    task_stack.push(task);

    while (!task_stack.empty())
    {
        simulation_map sim = task_stack.top();
        auto tview = sim.view;
        auto tfishes = sim.fishes;
        auto teat = sim.eat;
        task_stack.pop();
        cout << teat << endl;

        // move fish
        for (int i = 1; i < 17; i++)
        {
            coord cur_fish_coord = tfishes[i];
            coord new_coord;
            // removed fish.
            if (cur_fish_coord.x == -1)
                continue;
            fish cur_fish = tview[cur_fish_coord.x][cur_fish_coord.y];
            int cur_fish_num = cur_fish.num;
            int cur_fish_dir = cur_fish.dir;

            for(int dirp=0; dirp <8; dirp++) {
                cur_fish_dir = (cur_fish.dir + dirp) % 8;
                new_coord.x = cur_fish_coord.x + dx[cur_fish_dir];
                new_coord.y = cur_fish_coord.y + dy[cur_fish_dir];
                if (new_coord.x >= 0 && new_coord.x < 4 && new_coord.y >= 0 && new_coord.y < 4 && tview[new_coord.x][new_coord.y].num != 0)
                {
                    fish swapfish = tview[new_coord.x][new_coord.y];
                    // swapfish exist.
                    if (swapfish.num > 0)
                    {
                        tfishes[swapfish.num] = cur_fish_coord;
                        tview[cur_fish_coord.x][cur_fish_coord.y] = swapfish;
                    }
                    else
                    {
                        // make leaved place empty.
                        tview[cur_fish_coord.x][cur_fish_coord.y].num = -1;
                    }
                    tfishes[cur_fish_num] = new_coord;
                    tview[new_coord.x][new_coord.y] = fish(cur_fish.num, cur_fish_dir);
                    break;
                }
            }
            // cout << " ------------------- "  << i << endl;
            // for(int m=0; m<4; m++) {
            //     for(int n=0; n<4; n++) {
            //         cout << tview[m][n].num << " ";
            //     }
            //     cout << endl;
            // }
        }

        // shark eat
        coord cur_shark_coord = tfishes[0];
        fish cur_shark = tview[cur_shark_coord.x][cur_shark_coord.y];
        bool finish_flag = true;

        for(int i=1; i<4; i++) {
            coord new_shark_coord = coord(cur_shark_coord.x + dx[cur_shark.dir]*i, cur_shark_coord.y + dy[cur_shark.dir]*i);
            if(new_shark_coord.x < 0 || new_shark_coord.y < 0 || new_shark_coord.x >= 4 || new_shark_coord.y >= 4) continue;
            if(tview[new_shark_coord.x][new_shark_coord.y].num == -1) continue;
            finish_flag = false;

            fish eaten_fish = tview[new_shark_coord.x][new_shark_coord.y];
            // cout << "EAT : " << eaten_fish.num << endl;
            simulation_map newsim;

            newsim.eat = teat + eaten_fish.num;
            for(int j=0; j<17; j++) {
                newsim.fishes[j] = tfishes[j];
            }
            for(int j=0; j<4; j++) {
                for(int k=0; k<4; k++) {
                    newsim.view[j][k] = tview[j][k];
                }
            }
            newsim.fishes[0] = new_shark_coord;
            newsim.view[cur_shark_coord.x][cur_shark_coord.y].num = -1;
            newsim.view[new_shark_coord.x][cur_shark_coord.y] = fish(0, eaten_fish.dir);
            task_stack.push(newsim);
        }

        if(finish_flag) {
            eat_max = eat_max > teat ? eat_max : teat;
        }
    }

    cout << eat_max << endl;
}