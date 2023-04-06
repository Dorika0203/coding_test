#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
typedef struct pair<int, int> intp;

int N, H, M; // (2~10, 1~30, 0~(N-1)*H)
int origin_mat[31][10];
bool row_flag[30][9];
int faith[10];
int ans;
int row_cnt;


bool is_ans() {
    for(int i=0; i<N; i++) {
        if(faith[i] != i) return false;
    }
    return true;
}


void add_row(intp row) {
    int c1 = row.second;
    int c2 = c1+1;

    int o1 = origin_mat[row.first][c1];
    int o2 = origin_mat[row.first][c2];
    
    for(int i=row.first+1; i<H+1; i++) {
        for(int j=0; j<N; j++) {
            if(origin_mat[i][j] == o1) origin_mat[i][j] = o2;
            else if(origin_mat[i][j] == o2) origin_mat[i][j] = o1;
        }
    }
    swap(faith[o1], faith[o2]);
    row_flag[row.first][c1] = true;
    row_cnt++;
}


void remove_row(intp row) {
    int c1 = row.second;
    int c2 = c1+1;

    int o1 = origin_mat[row.first][c1];
    int o2 = origin_mat[row.first][c2];
    
    for(int i=row.first+1; i<H+1; i++) {
        for(int j=0; j<N; j++) {
            if(origin_mat[i][j] == o1) origin_mat[i][j] = o2;
            else if(origin_mat[i][j] == o2) origin_mat[i][j] = o1;
        }
    }
    swap(faith[o1], faith[o2]);
    row_flag[row.first][c1] = false;
    row_cnt--;
}


void solve(int r, int c) {
    if(row_cnt == 3) return;

    if(row_flag[r][c]) {
        if(c+1 < N-1) solve(r, c+1);
        else if(r+1 < H) solve(r+1, 0);
        return;
    }

    if(c < N-2 && row_flag[r][c+1]) {
        solve(r, c+1);
        return;
    }

    if((c > 0 && row_flag[r][c-1])) {
        if(c+1 < N-1) solve(r,c+1);
        else if(r+1 < H) solve(r+1, 0);
        return;
    }
    add_row(intp(r, c));
    if(is_ans()) {
        ans = ans < row_cnt ? ans : row_cnt;
    }
    solve(r, c+1);
    remove_row(intp(r,c));
    row_flag[r][c] = false;
    if(c+1 < N-1) solve(r, c+1);
    else if(r+1 < H) solve(r+1, 0);
    return;
}

int main()
{
    cin >> N >> M >> H;
    vector<intp> row_arr;
    int t1, t2;
    for(int i=0; i<M; i++) {
        cin >> t1 >> t2;
        row_arr.push_back(intp(t1-1, t2-1));
    }
    for(int i=0; i<H+1; i++) {
        for(int j=0; j<N; j++) {
            origin_mat[i][j] = j;
        }
    }
    for(int i=0; i<N; i++) {
        faith[origin_mat[H][i]] = i;
    }
    memset(row_flag, 0, 30*9);
    ans = 4;
    for(int i=0; i<row_arr.size(); i++) {
        add_row(row_arr[i]);
    }    
    row_cnt = 0;
    if(is_ans()) {
        cout << 0 << endl;
        return 0;
    }
    solve(0, 0);
    if(ans == 4) ans = -1;
    cout << ans << endl;
    return 0;
}