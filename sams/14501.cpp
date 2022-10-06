#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef pair<int, int> sch;

int main()
{
    int N;
    map<int, vector<sch>> schs;

    cin >> N;
    int* best_arr = new int[N+1];

    for(int i=0; i<N; i++) {
        int end, earn;
        cin >> end >> earn;
        end = end + i;

        auto iter = schs.find(end);

        if(iter == schs.end()) {
            vector<sch> arr;
            arr.push_back(sch(i+1, earn));
            schs.insert({end, arr});
        }
        else {
            iter->second.push_back(sch(i+1, earn));
        }
    }

    best_arr[0] = 0;
    for(int i=1; i<N+1; i++) {
        auto iter = schs.find(i);
        if(iter == schs.end()) {
            best_arr[i] = best_arr[i-1];
        }
        else {
            vector<sch> arr = iter->second;
            best_arr[i] = best_arr[i-1];
            for(int j=0; j<arr.size(); j++) {
                sch tmp = arr.at(j);
                int new_max = best_arr[tmp.first-1] + tmp.second;
                best_arr[i] = best_arr[i] > new_max ? best_arr[i] : new_max;
            }
        }
    }

    cout << best_arr[N] << endl;
}