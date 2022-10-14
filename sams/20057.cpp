#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> coord;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int ratio[10] = {55, 5, 1, 2, 7, 10, 1, 2, 7, 10};

vector<coord> get_coords(coord cc, int cd)
{
    // 45 5 (L)1 2 7 10 (R)1 2 7 10
    int L = (cd + 1) % 4;
    int R = (cd + 3) % 4;
    int B = (cd + 2) % 4;
    int F = cd % 4;

    vector<coord> coords;
    coords.push_back(coord(cc.first + dx[F], cc.second + dy[F]));
    coords.push_back(coord(cc.first + 2 * dx[F], cc.second + 2 * dy[F]));

    coords.push_back(coord(cc.first + dx[L] + dx[B], cc.second + dy[L] + dy[B]));
    coords.push_back(coord(cc.first + 2 * dx[L], cc.second + 2 * dy[L]));
    coords.push_back(coord(cc.first + dx[L], cc.second + dy[L]));
    coords.push_back(coord(cc.first + dx[L] + dx[F], cc.second + dy[L] + dy[F]));

    coords.push_back(coord(cc.first + dx[R] + dx[B], cc.second + dy[R] + dy[B]));
    coords.push_back(coord(cc.first + 2 * dx[R], cc.second + 2 * dy[R]));
    coords.push_back(coord(cc.first + dx[R], cc.second + dy[R]));
    coords.push_back(coord(cc.first + dx[R] + dx[F], cc.second + dy[R] + dy[F]));

    return coords;
}

int main()
{
    int N;
    cin >> N;
    int sand[N][N];
    coord tor = coord(N / 2, N / 2);
    int tord = 0;

    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            cin >> sand[x][y];
        }
    }

    int duration = 1;
    int tstep = 0;
    int step = 0;
    int step_count = 0;
    int removed_sand = 0;
    while (tstep < N * N - 1)
    {
        tstep++;
        step++;

        // move tornado
        tor.first += dx[tord];
        tor.second += dy[tord];

        // go logic
        vector<coord> coords = get_coords(tor, tord);
        int moved_sand = 0;
        for (int i = 1; i<coords.size(); i++)
        {
            int ms = ratio[i] * sand[tor.first][tor.second] / 100;
            moved_sand += ms;

            if (coords[i].first < 0 || coords[i].second < 0 || coords[i].first >= N || coords[i].second >= N)
                removed_sand += ms;
            else
                sand[coords[i].first][coords[i].second] += ms;
        }

        int left = sand[tor.first][tor.second] - moved_sand;
        if (coords[0].first < 0 || coords[0].second < 0 || coords[0].first >= N || coords[0].second >= N)
            removed_sand += left;
        else
            sand[coords[0].first][coords[0].second] += left;

        sand[tor.first][tor.second] = 0;

        // step_count, tord, duration update.
        if (step % duration == 0)
        {
            step = 0;
            step_count++;
            tord = (tord + 1) % 4;
        }
        if (step_count == 2)
        {
            duration++;
            step_count = 0;
        }
    }

    cout << removed_sand << endl;
}