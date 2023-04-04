#include<iostream>

using namespace std;

int view[50][50];
int N, M;
int cr, cc, dir;
bool flag;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int main()
{
    scanf("%d %d", &N, &M);
    scanf("%d %d %d", &cr, &cc, &dir);
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &view[i][j]);
        }
    }
    int count = 0;

    while(true) {
        // clean
        if(view[cr][cc] == 0) count++;
        view[cr][cc] = 2;

        flag = true;
        for(int i=1; i<5; i++) {
            int ndir = dir + 3*i;
            ndir = ndir % 4;
            int nr = cr + dr[ndir];
            int nc = cc + dc[ndir];
            if(nr < 0 || nc < 0 || nr > N-1 || nc > M-1) continue;
            if(view[nr][nc] == 0) {
                flag = false;
                dir = ndir;
                cr = nr;
                cc = nc;
                break;
            }
        }
        if(flag) {
            int ndir = dir+2;
            ndir = ndir % 4;
            cr = cr + dr[ndir];
            cc = cc + dc[ndir];
            if(cr < 0 || cc < 0 || cr > N-1 || cc > M-1) break;
            if(view[cr][cc] == 1) break;
        }
    }
    cout << count << endl;
}