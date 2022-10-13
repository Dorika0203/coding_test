#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef pair<int, int> coord;


int dc[4] = {0, 0, 1, -1};
int dr[4] = {-1, 1, 0, 0};


class shark {
    public:

    int speed;
    int dir;
    int size;

    shark() {
        speed = 0;
        dir = 0;
        size = 0;
    }

    shark(int speed_, int dir_, int size_) {
        speed = speed_;
        dir = dir_;
        size = size_;
    }
};

int main()
{

    int R, C, M;
    cin >> R >> C >> M;
    vector<shark> sharks;
    map<coord, shark> sharkmap;
    map<coord, shark> sharkmap2;
    int ans = 0;

    for(int i=0; i<M; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        shark s = shark(c, d-1, e);
        sharkmap.insert({coord(a-1,b-1), s});
    }


    for(int sec=0; sec<C; sec++) {

        // cout << sharkmap.size() << ": ";
        // for(auto iter=sharkmap.begin(); iter!=sharkmap.end(); iter++) {
        //     cout << "(" << iter->first.first << ", " << iter->first.second << ") ";
        // }
        // cout << endl;

        // grap shark

        for(int j=0; j<R; j++) {
            auto iter = sharkmap.find(coord(j, sec));
            if(iter != sharkmap.end()) {
                ans += iter->second.size;
                sharkmap.erase(coord(j, sec));
                // cout << "EAT" << endl;
                break;
            }
        }

        // move shark

        for(auto iter = sharkmap.begin(); iter != sharkmap.end(); iter++) {

            coord tmp_loc = iter->first;
            shark tmp_shark = iter->second;

            tmp_loc = coord(tmp_loc.first + tmp_shark.speed*dr[tmp_shark.dir] , tmp_loc.second + tmp_shark.speed*dc[tmp_shark.dir]);

            if(tmp_loc.first < 0 || tmp_loc.first >= R) {
                tmp_loc.first = abs(tmp_loc.first);

                int change = tmp_loc.first / (R-1);
                int remain = tmp_loc.first % (R-1);
                if(change%2 == 0) {
                    tmp_loc.first = remain;
                    tmp_shark.dir = 1;
                }
                else {
                    tmp_loc.first = (R-1) - remain;
                    tmp_shark.dir = 0;
                }
            }
            else if(tmp_loc.second < 0 || tmp_loc.second >= C) {
                tmp_loc.second = abs(tmp_loc.second);

                int change = tmp_loc.second / (C-1);
                int remain = tmp_loc.second % (C-1);
                if(change % 2 == 0) {
                    tmp_loc.second = remain;
                    tmp_shark.dir = 2;
                }
                else {
                    tmp_loc.second = (C-1)-remain;
                    tmp_shark.dir = 3;
                }
            }

            auto iter2 = sharkmap2.find(tmp_loc);
            if(iter2 != sharkmap2.end()) {
                shark exist_shark = iter2->second;
                if(exist_shark.size < tmp_shark.size) {
                    sharkmap2.erase(tmp_loc);
                    sharkmap2.insert({tmp_loc, tmp_shark});
                }
            }
            else {
                sharkmap2.insert({tmp_loc, tmp_shark});
            }
        }

        sharkmap.clear();
        sharkmap = sharkmap2;
        map<coord, shark> new_empty_map;
        sharkmap2 = new_empty_map;
    }
    cout << ans << endl;
}