#include <iostream>
#include <vector>

using namespace std;

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

typedef pair<int, int> coord;

class fireball
{
public:
    coord loc;
    int mass;
    int dir;
    int speed;

    fireball()
    {
        loc = coord(0, 0);
        mass = 0;
        dir = 0;
        speed = 0;
    }

    fireball(coord l, int m, int d, int s)
    {
        loc = l;
        mass = m;
        dir = d;
        speed = s;
    }
};

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<fireball> fbArr;
    vector<int> view[N][N];

    for (int i = 0; i < M; i++)
    {
        int x, y, m, s, d;
        cin >> x >> y >> m >> s >> d;
        fireball newfb = fireball(coord(x - 1, y - 1), m, d, s);
        fbArr.push_back(newfb);
    }

    // simulation
    for (int move = 0; move < K; move++)
    {
        // update view
        for (int fbIdx = 0; fbIdx < fbArr.size(); fbIdx++)
        {
            fireball curfb = fbArr[fbIdx];
            coord newc = coord(curfb.loc.first + dx[curfb.dir] * curfb.speed, curfb.loc.second + dy[curfb.dir] * curfb.speed);
            if (newc.first < 0)
            {
                newc.first = abs(newc.first);
                newc.first = newc.first % N;
                newc.first = N - newc.first;
            }
            if (newc.second < 0)
            {
                newc.second = abs(newc.second);
                newc.second = newc.second % N;
                newc.second = N - newc.second;
            }
            newc.first = newc.first % N;
            newc.second = newc.second % N;
            view[newc.first][newc.second].push_back(fbIdx);
        }

        // remove and create fireball, update fireball Arr
        vector<fireball> newfbArr;

        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y < N; y++)
            {
                if (view[x][y].empty())
                    continue;

                if (view[x][y].size() == 1)
                {
                    int idx = view[x][y][0];
                    newfbArr.push_back(fireball(coord(x, y), fbArr[idx].mass, fbArr[idx].dir, fbArr[idx].speed));
                }
                else
                {
                    int mass_sum = 0;
                    int speed_sum = 0;
                    int count = view[x][y].size();
                    int d = fbArr[view[x][y][0]].dir % 2;
                    bool dirflag = true;
                    for (auto iter = view[x][y].begin(); iter != view[x][y].end(); iter++)
                    {
                        int idx = *iter;
                        fireball curfb = fbArr[idx];
                        mass_sum += curfb.mass;
                        speed_sum += curfb.speed;
                        if (curfb.dir % 2 != d)
                            dirflag = false;
                    }
                    int new_mass = mass_sum / 5;
                    int new_speed = speed_sum / count;
                    int new_dir[4] = {1, 3, 5, 7};
                    if (new_mass == 0) {
                        view[x][y].clear();
                        continue;
                    }

                    if (dirflag)
                    {
                        new_dir[0] = 0;
                        new_dir[1] = 2;
                        new_dir[2] = 4;
                        new_dir[3] = 6;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        fireball newfb = fireball(coord(x, y), new_mass, new_dir[i], new_speed);
                        newfbArr.push_back(newfb);
                    }
                }
                view[x][y].clear();
            }
        }

        fbArr.clear();
        for (int i = 0; i < newfbArr.size(); i++)
        {
            fbArr.push_back(newfbArr[i]);
        }

        // cout << fbArr.size() << endl;
    } // sim done.


    int mass_sum = 0;
    for (int i = 0; i < fbArr.size(); i++)
    {
        mass_sum += fbArr[i].mass;
    }


    cout << mass_sum << endl;
}
