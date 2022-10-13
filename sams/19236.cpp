#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
typedef pair<int, int> coord;

class fish
{
public:
    int dir;
    coord loc;

    fish(int d, coord l) {
        dir = d;
        loc = l;
    }

    fish() {
        dir = -1;
        loc = coord(-1, -1);
    }
};

class shark
{
    public:
    int dir;
    coord loc;
    int eaten;

    shark(int d, coord l, int e) {
        dir = d;
        loc = l;
        eaten = e;
    }

    shark() {
        dir = -1;
        loc = coord(-1, -1);
        eaten = 0;
    }
};

int main()
{
    stack<pair<shark, fish*>> sim_stack;
    fish fishes[17];
    shark s;
    int max_eat = 0;

    for(int i=0; i<16; i++) {
        int num, dir;
        cin >> num >> dir;
        fishes[num] = fish(dir-1, coord(i/4, i%4));
    }

    // shark init
    for(int i=1; i<17; i++) {
        if(fishes[i].loc.first == 0 && fishes[i].loc.second == 0) {
            s.dir = fishes[i].dir;
            s.loc = fishes[i].loc;
            fishes[i].dir = -1;
            s.eaten += i;
            break;
        }
    }

    sim_stack.push(pair<shark, fish*>(s, fishes));

    while(!sim_stack.empty()) {

        auto simmap = sim_stack.top();
        sim_stack.pop();
        shark s = simmap.first;
        fish* fishes = simmap.second;

        cout << "--------" << endl;
        cout << s.eaten << endl;

        // move fish
        for(int i=1; i<17; i++) {

            coord loc = fishes[i].loc;
            int dir = fishes[i].dir;
            if(dir == -1) continue;

            int newy = loc.first + dy[dir];
            int newx = loc.second + dx[dir];

            if(newy >= 0 && newy < 4  && newx >= 0 && newx < 4 && !(s.loc.first == newy && s.loc.second == newx)) {
                // swap or move fish.
                for(int j=1; j<17; j++) {
                    if(i == j) continue;
                    if(fishes[j].loc.first == newy && fishes[j].loc.second == newx) {
                        fishes[j].loc = loc;
                        break;
                    }
                }
                fishes[i].loc.first = newy;
                fishes[i].loc.second = newx;
            }

            // dir change and try again.
            else {
                dir = (dir+1)%8;
                newy = loc.first + dy[dir];
                newx = loc.second + dx[dir];
                if(newy >= 0 && newy < 4  && newx >= 0 && newx < 4 && !(s.loc.first == newy && s.loc.second == newx)) {
                    // swap or move fish.
                    for(int j=1; j <17; j++) {
                        if(i == j) continue;
                        if(fishes[j].loc.first == newy && fishes[j].loc.second == newx) {
                            fishes[j].loc = loc;
                            break;
                        }
                    }
                    fishes[i].loc.first = newy;
                    fishes[i].loc.second = newx;
                    fishes[i].dir = dir;
                }
            }
        }

        for(int j=1; j<17; j++) {
            if(fishes[j].dir != -1) {
                cout << j << ": (" << fishes[j].loc.first << ", " << fishes[j].loc.second << ")" << endl;
            }
        }

        // shark eat
        bool movable = false;
        for(int i=1; i<4; i++) {
            coord loc = s.loc;
            int dir = s.dir;
            int newy = loc.first + dy[dir]*i;
            int newx = loc.second + dx[dir]*i;

            if(newx < 0 || newx >= 4 || newy < 0 || newy >= 4) continue;
            for(int j=1; j<17; j++) {
                if(fishes[j].dir == -1) continue;
                if(fishes[j].loc.first == newy && fishes[j].loc.second == newx) {
                    movable = true;
                    shark newmap_shark;
                    fish newmap_fishes[17];
                    newmap_shark.dir = fishes[j].dir;
                    newmap_shark.loc = coord(newy, newx);
                    newmap_shark.eaten = s.eaten + j;

                    for(int k=1; k<17; k++) {
                        newmap_fishes[k] = fishes[k];
                    }
                    newmap_fishes[j].dir = -1;
                    cout << "EAT " << j << endl;
                    sim_stack.push(pair<shark, fish*>(newmap_shark, newmap_fishes));
                }
            }
        }

        if(!movable) {
            max_eat = max_eat > s.eaten ? max_eat : s.eaten;
        }
    }
    cout << max_eat << endl;
}