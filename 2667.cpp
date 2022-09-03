// 단지 번호 붙이기, DFS, BFS

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
    int N;
    cin >> N;

    vector<vector<char>> house_map(N, vector<char>(N,0));

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++){
            cin >> house_map[i][j];
            house_map[i][j] -= '0';
        }
    }

    vector<int> town;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(house_map[i][j] == 1) {

                stack<pair<int, int>> task;
                task.push(pair<int, int>(i, j));
                house_map[i][j] = 0;

                int n_house = 0;
                while(!task.empty())
                {
                    pair<int, int> tmp = task.top();
                    task.pop();
                    n_house += 1;

                    for(int i=0; i<4; i++)
                    {
                        int nx = tmp.first + dx[i];
                        int ny = tmp.second + dy[i];

                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        if (house_map[nx][ny] == 0) continue;

                        task.push(pair<int, int>(nx, ny));
                        house_map[nx][ny] = 0;
                    }
                }
                town.push_back(n_house);
            }
        }
    }

    cout << town.size() << endl;
    sort(town.begin(), town.end());
    for(auto iter=town.begin(); iter != town.end(); iter++)
    {
        cout << *iter << endl;
    }

}