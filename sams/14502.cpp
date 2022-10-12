#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
typedef pair<int, int> coord;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

coord get_point(int val)
{
    int y, x;
    x = val % 8;
    y = val / 8;
    return coord(y, x);
}

int main()
{
    int N, M;
    cin >> N >> M;
    int view[N][M];
    int view2[N][M];
    int num_wall = 0;
    vector<coord> virus;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> view[i][j];
            if (view[i][j] == 1)
                num_wall++;
            if (view[i][j] == 2)
                virus.push_back(coord(i, j));
        }
    }

    int max_wall = 1 << 18;
    int idx[3];
    int flag = 0;
    coord idx_coord[3];
    queue<coord> task;

    int max_virus_free = -1;
    int n_virus = 0;
    num_wall += 3;

    for (int bitmap = 0; bitmap < max_wall; bitmap++)
    {
        idx[0] = bitmap % 64;
        idx[1] = (bitmap / 64) % 64;
        idx[2] = (bitmap / 4096) % 64;

        if (!(idx[0] < idx[1] && idx[1] < idx[2]))
            continue;

        for (int i = 0; i < 3; i++)
        {
            idx_coord[i] = get_point(idx[i]);
            if (idx_coord[i].first >= N || idx_coord[i].second >= M)
                break;
            if (view[idx_coord[i].first][idx_coord[i].second] != 0)
                break;
            flag = i;
        }
        if (flag != 2)
            continue;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                view2[i][j] = view[i][j];
            }
        }

        view2[idx_coord[0].first][idx_coord[0].second] = 1;
        view2[idx_coord[1].first][idx_coord[1].second] = 1;
        view2[idx_coord[2].first][idx_coord[2].second] = 1;

        for (int i = 0; i < virus.size(); i++)
        {
            task.push(virus[i]);
        }

        n_virus = 0;
        while (!task.empty())
        {
            coord tmp = task.front();

            for (int i = 0; i < 4; i++)
            {
                int ny = dy[i] + tmp.first;
                int nx = dx[i] + tmp.second;
                if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                    continue;
                if (view2[ny][nx] != 0)
                    continue;
                view2[ny][nx] = 2;
                task.push(coord(ny, nx));
            }
            n_virus++;
            task.pop();
        }
        if (max_virus_free < N * M - num_wall - n_virus)
        {
            max_virus_free = N * M - num_wall - n_virus;
        }
    }
    cout << max_virus_free << endl;
}