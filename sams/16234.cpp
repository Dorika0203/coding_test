#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
typedef struct pair<int,int> intp;

bool fview[50][50];
int pview[50][50];
int N, L, R;

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

int main()
{
    cin >> N >> L >> R;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> pview[i][j];
        }
    }

    int ans = 0;

    while(ans <= 2000) {
        int ucount = 0;
        memset(fview, 0, 2500);
        
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {

                if(fview[i][j]) continue;

                ucount++;
                queue<intp> task;
                vector<intp> united;
                int sum = 0;

                fview[i][j] = true;
                task.push(intp(i,j));

                while(!task.empty()) {

                    int r = task.front().first;
                    int c = task.front().second;
                    int p = pview[r][c];

                    sum += p;
                    united.push_back(intp(r,c));

                    task.pop();

                    for(int dir=0; dir<4; dir++) {
                        int nr = r+dr[dir];
                        int nc = c+dc[dir];
                        if(nr<0 || nr > N-1 || nc < 0 || nc > N-1) continue;
                        if(abs(pview[nr][nc] - p) < L || abs(pview[nr][nc]-p) > R) continue;
                        if(fview[nr][nc]) continue;

                        fview[nr][nc] = true;
                        task.push(intp(nr, nc));
                    }
                }
                sum = sum / united.size();
                for(auto i = united.begin(); i != united.end(); i++) {
                    pview[i->first][i->second] = sum;
                }
            }
        }
        if(ucount == N*N) break;
        ans++;
    }
    cout << ans << endl;
}