#include <iostream>

using namespace std;
typedef pair<int, int> coord;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

class room {
    public:
    int sIdx;
    int lTime;

    room() {
        sIdx = 0;
        lTime = 0;
    }

    room(int s, int t) {
        sIdx = s;
        lTime = t;
    }
};

class shark {
    public:

    int dir;
    int p[4][4];
    coord loc;
};


int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    room view[N][N];
    shark sharkArr[M];

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int num;
            cin >> num;
            if(num > 0) {
                view[i][j] = room(num, K);
                sharkArr[num-1].loc = coord(i,j);
            }
        }
    }

    for(int i=0; i<M; i++) {
        int dir;
        cin >> dir;
        sharkArr[i].dir = dir-1;
    }

    for(int i=0; i<M; i++) {
        for(int j=0; j<4; j++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a--;
            b--;
            c--;
            d--;
            sharkArr[i].p[j][0] = a;
            sharkArr[i].p[j][1] = b;
            sharkArr[i].p[j][2] = c;
            sharkArr[i].p[j][3] = d;
        }
    }

    // cout << endl;
    // for(int i=0; i<M; i++) {
    //     for(int j=0; j<4; j++) {
    //         cout << sharkArr[i].dir << " ";
    //         for(int k=0; k<4; k++) {
    //             cout << sharkArr[i].p[j][k]+1 << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    int sec = 0;
    int removed_shark = 0;

    while(true) {

        // cout << "SEC ------ " << sec << endl;
        // for(int i=0; i<N; i++) {
        //     for(int j=0; j<N; j++) {
        //         cout << "(" << view[i][j].sIdx << "," << view[i][j].lTime << ") ";
        //     }
        //     cout << endl;
        // }
        sec ++;

        // move shark
        for(int sIdx=0; sIdx<M; sIdx++) {
            shark curShark = sharkArr[sIdx];
            if(curShark.dir == -1) continue;

            // try empty room
            bool is_moveable = false;
            for(int j=0; j<4; j++) {
                coord newloc = coord(curShark.loc.first + dx[curShark.p[curShark.dir][j]], curShark.loc.second + dy[curShark.p[curShark.dir][j]]);
                if(newloc.first < 0 || newloc.second < 0 || newloc.first >= N || newloc.second >= N) continue;
                if(view[newloc.first][newloc.second].sIdx != 0) continue;

                sharkArr[sIdx].dir = curShark.p[curShark.dir][j];
                sharkArr[sIdx].loc= newloc;
                is_moveable = true;
                break;
            }
            if(is_moveable) continue;

            // try my smell room
            for(int j=0; j<4; j++) {
                coord newloc = coord(curShark.loc.first + dx[curShark.p[curShark.dir][j]], curShark.loc.second + dy[curShark.p[curShark.dir][j]]);
                if(newloc.first < 0 || newloc.second < 0 || newloc.first >= N || newloc.second >= N) continue;
                if(view[newloc.first][newloc.second].sIdx != sIdx+1) continue;

                sharkArr[sIdx].dir = curShark.p[curShark.dir][j];
                sharkArr[sIdx].loc= newloc;
                break;
            }
        }

        // skunk

        for(int sIdx=0; sIdx<M; sIdx++) {
            shark curShark = sharkArr[sIdx];
            if(curShark.dir == -1) continue;
            room v = view[curShark.loc.first][curShark.loc.second];

            if(v.sIdx == 0 || v.sIdx == sIdx+1) {
                view[curShark.loc.first][curShark.loc.second] = room(sIdx+1, K+1);
            }
            // collision
            else {
                if(v.lTime != K+1) {
                  cout << "ERROR" << endl;
                  return -1;  
                }
                removed_shark++;
                int collision_idx = v.sIdx;
                if(collision_idx < sIdx+1) {
                    sharkArr[sIdx].dir = -1;
                }
                else {
                    view[curShark.loc.first][curShark.loc.second] = room(sIdx+1, K+1);
                    sharkArr[collision_idx-1].dir = -1;
                }
            }
        }

        // smell time reduction
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                view[i][j].lTime = view[i][j].lTime == 0 ? 0 : view[i][j].lTime-1;
                if(view[i][j].lTime == 0) view[i][j].sIdx = 0;
            }
        }
        if(removed_shark == M-1) break;
        if(sec == 1000) break;
    }

    if(removed_shark == M-1) cout << sec << endl;
    else cout << -1 << endl;
}