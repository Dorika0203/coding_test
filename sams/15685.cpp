#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

typedef struct pair<int,int> coord;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int N;
coord d_start[20];
int d_dir[20];
int d_gen[20];

bool view[101][101];

coord rotate(coord target, coord axis) {

    target.first -= axis.first;
    target.second -= axis.second;
    swap(target.first, target.second);
    target.second = -target.second;
    target.first += axis.first;
    target.second += axis.second;
    return target;   
}

int main()
{
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> d_start[i].first >> d_start[i].second >> d_dir[i] >> d_gen[i];
    }
    memset(view, 0x00, 101*101);
    int ans = 0;

    for(int i=0; i<N; i++) {
        int gen = d_gen[i];
        coord start = coord(d_start[i].first, -d_start[i].second);
        int dir = d_dir[i];
        vector<coord> parr;
        parr.push_back(start);
        parr.push_back(coord(start.first+dx[dir], start.second-dy[dir]));
        coord axis = parr.back();
        view[start.first][-start.second] = true;
        view[axis.first][-axis.second] = true;

        for(int j=0; j<gen; j++) {
            axis = parr.back();
            int sidx = parr.size()-2;
            for(int k=sidx; k>=0; k--) {
                coord found = rotate(parr[k], axis);
                view[found.first][-found.second] = true;
                parr.push_back(found);
            }
        }
    }

    for(int x=0; x<100; x++) {
        for(int y=0; y<100; y++) {
            if(view[x][y] && view[x][y+1] && view[x+1][y] && view[x+1][y+1]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}