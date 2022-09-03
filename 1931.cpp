// 회의실 배정, 그리디

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> T;

static bool compare_T(T a, T b)
{
    if(a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main()
{
    int N;
    cin >> N;

    vector<T> meetings;

    for(int i=0; i<N; i++)
    {
        int a, b;
        cin >> a >> b;
        meetings.push_back(T(a, b));
    }

    sort(meetings.begin(), meetings.end(), compare_T);

    int current_time = 0;
    int counter = 0;
    for(auto iter = meetings.begin(); iter != meetings.end(); iter++)
    {
        T tmp = *iter;
        if(current_time > tmp.first) continue;
        current_time = tmp.second;
        counter += 1;
    }

    cout << counter << endl;
}