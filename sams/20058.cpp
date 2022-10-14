#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

typedef pair<int, int> coord;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main()
{
    int N, Q;
    cin >> N >> Q;
    int M = 1<<N;
    int view[M][M];
    int levelArr[Q];
    
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            cin >> view[i][j];
        }
    }

    for(int i=0; i<Q; i++) {
        cin >> levelArr[i];
    }

    for(int stage=0; stage<Q; stage++) {
        int level = levelArr[stage];
        int m = 1 << level;
        int n = M / m;


        // ROTATE
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                // x: (i*m) ~ (i+1)*m-1
                // y: (j*m) ~ (j+1)*m-1
                int tmp[m][m];
                for(int x=0; x<m; x++) {
                    for(int y=0; y<m; y++) {
                        tmp[y][m-1-x] = view[i*m+x][j*m+y];
                    }
                }
                for(int x=0; x<m; x++) {
                    for(int y=0; y<m; y++) {
                        view[i*m+x][j*m+y] = tmp[x][y];
                    }
                }
            }
        }

        // ICE_CHECK
        vector<coord> melt_pos;
        for(int x=0; x<M; x++) {
            for(int y=0; y<M; y++) {
                int count = 0;
                for(int i=0; i<4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(nx < 0 || ny < 0 || nx >= M || ny >= M) continue;
                    if(view[nx][ny] == 0) continue;
                    count++;
                }
                if(count<3)
                    melt_pos.push_back(coord(x,y));
            }
        }
        for(int i=0; i<melt_pos.size(); i++) {
            coord pos = melt_pos[i];
            view[pos.first][pos.second] = max(0, view[pos.first][pos.second]-1);
        }
    }

    int ice_sum = 0;
    int max_weight = 0;

    for(int x=0; x<M; x++) {
        for(int y=0; y<M; y++) {
            ice_sum += view[x][y];
        }
    }

    for(int x=0; x<M; x++) {
        for(int y=0; y<M; y++) {
            if(view[x][y] == 0) continue;
            queue<coord> task;
            view[x][y] = 0;
            task.push(coord(x,y));
            int weight = 0;
            while(!task.empty()) {
                coord p = task.front();
                weight++;
                task.pop();

                for(int i=0; i<4; i++) {
                    int nx = p.first + dx[i];
                    int ny = p.second + dy[i];
                    if(nx < 0 || ny < 0 || nx >= M || ny >= M) continue;
                    if(view[nx][ny] == 0) continue;
                    view[nx][ny] = 0;
                    task.push(coord(nx, ny));
                }
            }
            max_weight = max_weight > weight ? max_weight : weight;
        }
    }
    cout << ice_sum << endl;
    cout << max_weight << endl;
}