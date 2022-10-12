#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;

    int del_count = 0;
    int pick_count = 0;
    int p2 = deliveries.size()-1;
    int p1 = p2;
    int p_next = 0;

    bool start_flag = false;
    bool del_full = false;
    bool pick_full = false;

    while(true)
    {
        // cout << p1 << " " << p2 << " " << p_next << "    " << del_count << " " << pick_count << endl;
        // cout << p1 << " " << p2 << endl;
        // cout << deliveries[0] << " " << deliveries[1] << " " << deliveries[2] << " " << deliveries[3] << " " << deliveries[4] << endl;
        // cout << pickups[0] << " " << pickups[1] << " " << pickups[2] << " " << pickups[3] << " " << pickups[4] << endl << endl;

        if(!start_flag && deliveries[p1] == 0 && pickups[p1] == 0) {
            p2--;
            p1 = p2;
            continue;
        }

        start_flag = true;
        del_count += deliveries[p1];
        pick_count += pickups[p1];
        deliveries[p1] = 0;
        pickups[p1] = 0;

        if(del_count >= cap) {
            deliveries[p1] = del_count - cap;
            del_count = cap;
            del_full = true;
            p_next = p_next > p1 ? p_next : p1;
        }

        if(pick_count >= cap) {
            pickups[p1] = pick_count - cap;
            pick_count = cap;
            pick_full = true;
            p_next = p_next > p1 ? p_next : p1;
        }

        if(del_full && pick_full) {
            answer += (p2+1) * 2;
            p1 = p2 = p_next;
            // cout << "FULL " << p_next <<  " " << answer << endl;
            del_count = pick_count = 0;
            start_flag = del_full = pick_full = false;
            continue;
        }

        if(p1 == 0) {
            answer += (p2+1)*2;
            // cout << "DONE " << p_next <<  " " << answer << endl;
            del_count = pick_count = 0;
            start_flag = del_full = pick_full = false;
            break;
        }
        p1 --;
    }

    return answer;
}