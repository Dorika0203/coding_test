#include <iostream>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

typedef struct pair<int,int> pii;

int pview[22][22];
int parr[5];
int x, y;
int N;
int sum;
bool d_flag_mat[22][22];

int get_diff() {
    int check_min = 0x7fffffff;
    int check_max = 0;

    for(int i=0; i<5; i++) {
        check_min = check_min < parr[i] ? check_min : parr[i];
        check_max = check_max > parr[i] ? check_max : parr[i];
    }
    return check_max - check_min;
}

int solver(pii task) {
    // cout << "SOLVING " << task.first << "," << task.second << endl;
    int d1 = task.first;
    int d2 = task.second;
    d_flag_mat[d1][d2] = false;
    memset(parr, 0, 5*sizeof(int));
    for(int row=1; row<x+d1; row++) {
        for(int col=1; col <= y && row+col<x+y; col++) {
            parr[0] += pview[row][col];
        }
    }
    for(int row=1; row<=x+d2; row++) {
        for(int col=N; col >=y+1 && row-col<x-y; col--) {
            parr[1] += pview[row][col];
        }
    }
    for(int row=x+d1; row<=N; row++) {
        for(int col=1; col < y-d1+d2 && row-col>x-y+2*d1; col++) {
            parr[2] += pview[row][col];
        }
    }
    for(int row=x+d2+1; row<=N; row++) {
        for(int col=N; col>=y-d1+d2 && row+col>x+y+2*d2; col--) {
            parr[3] += pview[row][col];
        }
    }
    parr[4] = sum - (parr[0] + parr[1] + parr[2] + parr[3]);
    int retval = get_diff();
    // cout << retval << endl;

    if(d1+d2+1 > N-x) return retval;

    if(d1 < y-1 && d_flag_mat[d1+1][d2]) {
        int val1 = solver(pii(d1+1, d2));
        retval = retval < val1 ? retval : val1;
    }
    if(d2 < N-y && d_flag_mat[d1][d2+1]) {
        int val2 = solver(pii(d1, d2+1));
        retval = retval < val2 ? retval : val2;
    }
    return retval;
}

int main()
{
    cin >> N;
    int min = 0x7fffffff;
    // x: (1 <= x <= N-1) y: (2 <= y <= N-1)

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> pview[i][j];
            sum += pview[i][j];
        }
    }

    for(x=1; x<N-1; x++) {
        for(y=2; y<N; y++) {
            memset(d_flag_mat, 1, 22*22*sizeof(bool));
            int ret = solver(pii(1,1));
            min = min < ret ? min : ret;
        }
    }
    cout << min << endl;
    return 0;
}