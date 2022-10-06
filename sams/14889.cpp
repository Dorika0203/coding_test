#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


int S[20][20];
int N;

pair<int, int> get_score(vector<int> &start, vector<int> &end) {

    int p_start, p_end;
    p_start = p_end = 0;
    for(int i=0; i<N/2; i++) {
        for(int j=0; j<N/2; j++) {
            p_start += S[start[i]][start[j]];
            p_end += S[end[i]][end[j]];
        }
    }

    return pair<int,int>(p_start, p_end);
}

bool set_team(vector<int> &start, vector<int> &end, int bitmap) {

    start.clear();
    end.clear();

    for(int i=0; i<N; i++) {
        int k = bitmap % 2;
        if(k) start.push_back(i);
        else end.push_back(i);
        bitmap = bitmap / 2;
    }

    if(start.size() != N/2) return false;
    return true;
}

int main()
{
    vector<int> start;
    vector<int> end;
    int max_bitmap = 0;
    int save_bitmap = 0;

    cin >> N;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> S[i][j];
        }
    }

    max_bitmap = pow(2, N/2) - 1;
    max_bitmap = max_bitmap * pow(2, N/2);
    int min_gap = 0x7fffffff;

    for(int bitmap=0; bitmap < max_bitmap; bitmap++) {
        if(!set_team(start, end, bitmap)) continue;
        pair<int, int> power = get_score(start, end);
        
        if(abs(power.first - power.second) < min_gap) {
            min_gap = abs(power.first - power.second);
            save_bitmap = bitmap;
        }
    }
    cout << min_gap << endl;

}