#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;

    long long del_n = 0;
    long long pic_n = 0;

    int del_cnt = 0;
    int pic_cnt = 0;
    int most_far = n-1;
    bool is_start = false;
    int tmp1 = -1;
    int tmp2 = -1;

    for(int i=n-1; i>=0; i--) {

        if(!is_start && deliveries[i] == 0) {
            most_far = i-1;
            continue;
        }

        is_start = true;
        del_cnt += deliveries[i];
        deliveries[i] = 0;

        if(del_cnt >= cap) {
            deliveries[i] = del_cnt - cap;
            del_cnt = cap;
            tmp1 = tmp1 == -1 ? i : tmp1;
        }

        if(tmp1 != -1) {
            del_n += (most_far+1) * 2;
            del_cnt = 0;
            most_far = tmp1;
            tmp1 = -1;
            is_start = false;
            i = most_far+1;
        }
    }

    if(del_cnt != 0) {
        del_n += (most_far+1) * 2;
    }

    is_start = false;
    for(int i=n-1; i>=0; i--) {

        if(!is_start && pickups[i] == 0) {
            most_far = i-1;
            continue;
        }

        is_start = true;
        pic_cnt += pickups[i];
        pickups[i] = 0;

        if(pic_cnt >= cap) {
            pickups[i] = pic_cnt - cap;
            pic_cnt = cap;
            tmp2 = tmp2 == -1 ? i : tmp2;
        }

        if(tmp2 != -1) {
            pic_n += (most_far+1) * 2;
            pic_cnt = 0;
            most_far = tmp2;
            tmp2 = -1;
            is_start = false;
            i = most_far+1;
        }
    }

    if(pic_cnt != 0) {
        pic_n += (most_far+1) * 2;
    }

    return answer;
}