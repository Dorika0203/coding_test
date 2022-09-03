// 기타 레슨, 이분 탐색

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> lecture_arr;
    int max_lecture_len = 0;
    int lecture_sum = 0;

    for(int i=0; i<N; i++)
    {
        int tmp;
        cin >> tmp;
        if(max_lecture_len < tmp) max_lecture_len = tmp;
        lecture_arr.push_back(tmp);
        lecture_sum += tmp;
    }

    int t_min = max_lecture_len;
    int t_max = 100000*10000+1;
    int t_check;

    while(true)
    {
        
        t_check = (t_min + t_max)/2;
        // cout << t_min << " " << t_max << " " << t_check << endl;

        int time_stamp = 0;
        int br_cnt = 0;
        for(int i=0; i<N; i++)
        {
            time_stamp += lecture_arr[i];
            if(time_stamp > t_check) {
                i -= 1;
                time_stamp = 0;
                br_cnt += 1;
            }
        }
        br_cnt += 1;

        if(t_min == t_max) break;
        if(br_cnt <= M) t_max = t_check;
        // t_check == t_min -> t_max = t_min OR t_min+1
        else if(t_check != t_min) t_min = t_check;
        else if(t_max != t_min) t_min += 1;
    }

    cout << t_check << endl;
}