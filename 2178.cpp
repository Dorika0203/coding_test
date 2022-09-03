// 미로 찾기, BFS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<char>> maze(N, vector<char>(M));
    vector<vector<int>> dist(N, vector<int>(M));
    queue<pair<int, int>> task;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> maze[i][j];
            maze[i][j] -= '0';
        }
    }

    task.push(pair<int, int>(0,0));
    maze[0][0] = 0;
    dist[0][0] = 1;

    pair<int, int> tmp;

    while(!task.empty()) {
        if(maze[N-1][M-1] == 0) break;
        tmp = task.front();
        task.pop();

        for(int i=0; i<4; i++) {
            int nx, ny;
            nx = tmp.first + dx[i];
            ny = tmp.second + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (maze[nx][ny] == 0) continue;

            task.push(pair<int, int>(nx, ny));
            maze[nx][ny] = 0;
            dist[nx][ny] = dist[tmp.first][tmp.second] + 1;
        }
    }

    cout << dist[N-1][M-1] << endl;
}