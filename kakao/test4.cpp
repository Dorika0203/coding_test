#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <queue>


using namespace std;

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;

    for(int i=0; i<numbers.size(); i++)
    {
        int n = numbers[i];
        string binn = "";
        while(n > 0) {
            binn.append(to_string(n%2));
            n = n/2;
        }

        int missing = 0;
        int k = 0;

        // 1은 예외처리 해야함
        if(n == 1) {
            answer.push_back(1);
            continue;
        }

        for(int j=2; j<6; j++) {
            if(binn.length() <= pow(2, j)-1) {
                missing = pow(2,j)-1 - binn.length();
                k = j-1;
                break;
            }
        }
        for(int j=0; j<missing; j++) binn.append("0");
        reverse(binn.begin(), binn.end());

        // BFS
        queue<pair<int, int>> task;
        task.push(pair<int, int>(pow(2, k), pow(2, k-1)));
        bool impossible_flag = false;

        while(!task.empty()) {

            pair<int, int> idx;
            idx = task.front();
            task.pop();

            // leaf
            if(idx.second == 0) continue;

            // non-leaf
            int par = idx.first;
            int lchild = idx.first - idx.second;
            int rchild = idx.first + idx.second;
            int dist_child_par = idx.second / 2;

            if(binn.at(par-1) == '0' && (binn.at(lchild-1) == '0' || binn.at(rchild-1) != '0')) {
                impossible_flag = true;
                break;
            }

            task.push(pair<int, int>(lchild, dist_child_par));
            task.push(pair<int, int>(rchild, dist_child_par));
        }

        if(impossible_flag) answer.push_back(0);
        else answer.push_back(1);
    }

    return answer;
}