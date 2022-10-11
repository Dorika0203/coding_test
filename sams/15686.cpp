#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> loc;
typedef unsigned int uint;

int main()
{
    int city[50][50];
    int N, M;
    vector<loc> house;
    vector<loc> chicken;

    cin >> N >> M;

    vector<int> select_idx;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++){
            cin >> city[i][j];
            if(city[i][j] == 1) house.push_back(loc(i, j));
            else if(city[i][j] == 2) chicken.push_back(loc(i,j));
        }
    }

    uint max_bitmap = 1 << chicken.size();

    int city_min = 0x7fffffff;
    for(uint bitmap = 0; bitmap < max_bitmap; bitmap++) {
        int tmp = bitmap;
        int count = 0;
        select_idx.clear();
        for(int i=0; i<chicken.size(); i++) {
            if(tmp%2 == 1) {
                select_idx.push_back(i);
                count++;
            }
            tmp = tmp / 2;
        }
        if(count != M) continue;

        int tmp_city_dist = 0;
        for(int i=0; i<house.size(); i++) {
            int house_min = 0x7fffffff;
            for(int j=0; j<select_idx.size(); j++) {
                int dist = abs(house[i].first-chicken[select_idx[j]].first) + abs(house[i].second-chicken[select_idx[j]].second);
                house_min = dist < house_min ? dist : house_min;
            }
            tmp_city_dist += house_min;
        }
        city_min = tmp_city_dist < city_min ? tmp_city_dist : city_min;
    }

    cout << city_min << endl;
}