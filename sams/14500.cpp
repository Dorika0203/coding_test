#include <iostream>

using namespace std;

typedef pair<int, int> coord;

bool isavailable(coord* arr, coord origin, int N, int M) {
    for(int i=0; i<3; i++) {
        if(origin.first+arr[i].first < 0 || origin.first+arr[i].first >= N) return false;
        if(origin.second+arr[i].second < 0 || origin.second+arr[i].second >= M) return false;
    }
    return true;
}

int main()
{
    coord shape[19][3] = {
        {coord(0,1), coord(0,2), coord(0,3)},
        {coord(1,0), coord(2,0), coord(3,0)},

        {coord(0,1), coord(1,0), coord(1,1)},

        {coord(1,0), coord(2,0), coord(2,1)},
        {coord(1,0), coord(2,0), coord(2,-1)},
        {coord(-1,0), coord(-2,0), coord(-2,-1)},
        {coord(-1,0), coord(-2,0), coord(-2,1)},
        {coord(0,1), coord(0,2), coord(-1,2)},
        {coord(0,1), coord(0,2), coord(1,2)},
        {coord(0,-1), coord(0,-2), coord(-1,-2)},
        {coord(0,-1), coord(0,-2), coord(1,-2)},

        {coord(1,0), coord(1,1), coord(2,1)},
        {coord(1,0), coord(1,-1), coord(2,-1)},
        {coord(0,1), coord(1,1), coord(1,2)},
        {coord(0,-1), coord(1,-1), coord(1,-2)},

        {coord(0,-1), coord(0,1), coord(1,0)},
        {coord(0,-1), coord(0,1), coord(-1,0)},
        {coord(1,0), coord(-1,0), coord(0,1)},
        {coord(1,0), coord(-1,0), coord(0,-1)}

    };


    int N, M;
    cin >> N >> M;
    int view[N][M];

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> view[i][j];
        }
    }

    int max = 0x80000000;
    int tmp = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            coord origin = coord(i,j);
            for(int k=0; k<19; k++) {
                if(isavailable(shape[k], origin, N, M)) {
                    tmp = view[origin.first][origin.second];
                    tmp += view[shape[k][0].first + origin.first ][shape[k][0].second + origin.second ];
                    tmp += view[shape[k][1].first + origin.first ][shape[k][1].second + origin.second ];
                    tmp += view[shape[k][2].first + origin.first ][shape[k][2].second + origin.second ];
                    max = max > tmp ? max : tmp;
                }
            }
        }
    }

    cout << max << endl;
}