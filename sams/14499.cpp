#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> loc;

#define T 0
#define B 1
#define N 2
#define S 3
#define E 4
#define W 5


void swap_idx(int move, int* idx) {
    int tmp;
    switch(move) {
        case 1:
            tmp = idx[B];
            idx[B] = idx[E];
            idx[E] = idx[T];
            idx[T] = idx[W];
            idx[W] = tmp;
            break;
        case 2:
            tmp = idx[B];
            idx[B] = idx[W];
            idx[W] = idx[T];
            idx[T] = idx[E];
            idx[E] = tmp;
            break;
        case 3:
            tmp = idx[B];
            idx[B] = idx[N];
            idx[N] = idx[T];
            idx[T] = idx[S];
            idx[S] = tmp;
            break;
        case 4:
            tmp = idx[B];
            idx[B] = idx[S];
            idx[S] = idx[T];
            idx[T] = idx[N];
            idx[N] = tmp;
            break;
        default:
            cout << "ERROR" << endl;
            break;
    }
}


int main()
{
    int n, m;
    int x, y;
    int K;
    int val[6] = {0, 0, 0, 0, 0, 0};
    int idx[6] = {0,5,1,4,2,3};
    // top, bottom, north, south, east, west

    cin >> n >> m >> x >> y >> K;
    loc location = loc(x,y);

    int view[n][m];

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> view[i][j];
        }
    }

    vector<int> op;
    for(int i=0; i<K; i++) {
        int tmp;
        cin >> tmp;
        op.push_back(tmp);
    }

    vector<int> tval;
    for(int i=0; i<op.size(); i++) {
        loc new_location = location;
        switch(op[i]){
            case 1:
                new_location.second += 1;
                break;
            case 2:
                new_location.second -= 1;
                break;
            case 3:
                new_location.first -= 1;
                break;
            case 4:
                new_location.first += 1;
                break;
            default:
                break;
        }

        if(new_location.first < 0 || new_location.first >= n || new_location.second < 0 || new_location.second >= m)
            continue;
        
        location = new_location;
        swap_idx(op[i], idx);
        if(view[location.first][location.second] == 0) {
            view[location.first][location.second] = val[idx[B]];
        }
        else {
            val[idx[B]] = view[location.first][location.second];
            view[location.first][location.second] = 0;
        }

        tval.push_back(val[idx[T]]);
    }

    for(int i=0; i<tval.size(); i++) {
        cout << tval[i] << endl;
    }
}