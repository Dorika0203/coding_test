#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
typedef struct pair<int, int> intp;

int R, C, T; // Row, Column, sec
int A[50][50];
int spread[50][50];

int dr[4] = {0, -1, 0, 1}; // R, U, L, D
int dc[4] = {1, 0, -1, 0};

int cdir[4] = {1, 0, 3, 2}; // U R D L
int rdir[4] = {3, 0, 1, 2}; // D R U L

vector<intp> cwise;
vector<intp> rwise;

void print_view() {
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cin >> R >> C >> T;
    int cr, cc;
    int answer=0;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >> A[i][j];
            if(A[i][j] > 0) answer += A[i][j];
            if(A[i][j] == -1) {
                cr = i;
                cc = j;
            }
        }
    }
    cr--; // set upside

    // get upside coord vector
    int tr = cr + dr[cdir[0]];
    int tc = cc + dc[cdir[0]];
    cwise.push_back(intp(tr, tc));
    for(int didx=0; didx<4; didx++) {

        int cdr = dr[cdir[didx]];
        int cdc = dc[cdir[didx]];
        while(true) {
            tr += cdr;
            tc += cdc;
            if(tr < 0 || tr > cr || tc < 0 || tc > C-1) {
                tr -= cdr;
                tc -= cdc;
                break;
            }
            cwise.push_back(intp(tr, tc));
        }    
    }
    cwise.pop_back();

    // get downside coord vector;
    tr = cr+1 + dr[rdir[0]];
    tc = cc + dc[rdir[0]];
    rwise.push_back(intp(tr, tc));
    for(int didx=0; didx<4; didx++) {

        int cdr = dr[rdir[didx]];
        int cdc = dc[rdir[didx]];
        while(true) {
            tr += cdr;
            tc += cdc;
            if(tr < cr+1 || tr > R-1 || tc < 0 || tc > C-1) {
                tr -= cdr;
                tc -= cdc;
                break;
            }
            rwise.push_back(intp(tr, tc));
        }    
    }
    rwise.pop_back();

    // for(int i=0; i<cwise.size(); i++) {
    //     cout << cwise[i].first << "," << cwise[i].second << endl;
    // }
    // cout << endl;

    // for(int i=0; i<rwise.size(); i++) {
    //     cout << rwise[i].first << "," << rwise[i].second << endl;
    // }


    // SIMULATION
    for(int sec=0; sec<T; sec++) {

        // print_view();
        memset(spread, 0, 50*50*sizeof(int));
        
        // spread
        for(int i=0; i<R; i++) {
            for(int j=0; j<C; j++) {

                int amount = A[i][j]/5;
                for(int dir=0; dir<4; dir++) {
                    int nr = i + dr[dir];
                    int nc = j + dc[dir];
                    if(nr < 0 || nr > R-1 || nc < 0 || nc > C-1 || A[nr][nc] == -1) continue;
                    spread[nr][nc] += amount;
                    spread[i][j] -= amount;
                }
            }
        }
        for(int i=0; i<R; i++) {
            for(int j=0; j<C; j++) {
                A[i][j] += spread[i][j];
            }
        }

        // print_view();

        // activate upside
        answer = answer - A[cwise[0].first][cwise[0].second];
        for(int i=0; i<cwise.size()-1; i++) {
            A[cwise[i].first][cwise[i].second] = A[cwise[i+1].first][cwise[i+1].second];
        }
        A[cwise[cwise.size()-1].first][cwise[cwise.size()-1].second] = 0;
        // downside
        answer = answer - A[rwise[0].first][rwise[0].second];
        for(int i=0; i<rwise.size()-1; i++) {
            A[rwise[i].first][rwise[i].second] = A[rwise[i+1].first][rwise[i+1].second];
        }
        A[rwise[rwise.size()-1].first][rwise[rwise.size()-1].second] = 0;
    }
    cout << answer << endl;
}