#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
typedef unsigned int uint;

uint lrotate(uint rulet)
{
    uint tmp = rulet;
    tmp = tmp << 1;
    tmp += rulet >> 7;
    tmp = tmp % 256;
    return tmp;
}

uint rrotate(uint rulet)
{
    uint tmp = rulet;
    tmp = tmp >> 1;
    tmp += 128 * (rulet % 2);
    return tmp;
}

string get_str(uint rulet)
{
    string ret = "";
    for (int i = 0; i < 8; i++)
    {
        ret.append(to_string(rulet % 2));
        rulet = rulet / 2;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main()
{
    string tmp;
    uint rulet[4] = {0, 0, 0, 0};
    int N;
    vector<pair<int, int>> actions;

    for (int i = 0; i < 4; i++)
    {
        cin >> tmp;
        for (int j = 0; j < 8; j++)
        {
            if (tmp.at(j) == '1')
            {
                rulet[i] += 1 << (7 - j);
            }
        }
    }

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        actions.push_back(pair<int, int>(a, b));
    }

    stack<pair<int, int>> left_side;
    stack<pair<int, int>> right_side;
    for (int i = 0; i < actions.size(); i++)
    {
        pair<int, int> action = actions.at(i);
        // cout << " : " << action.first << endl;
        left_side.push(action);
        right_side.push(action);

        for (int j = action.first - 1; j >= 0; j--)
        {
            uint leftnode = (rulet[j] >> 5) % 2;
            uint rightnode = (rulet[j + 1] >> 1) % 2;
            if (leftnode != rightnode)
            {
                left_side.push(pair<int, int>(j, -1 * left_side.top().second));
            }
            else
                break;
        }
        for (int j = action.first + 1; j < 4; j++)
        {
            uint leftnode = (rulet[j - 1] >> 5) % 2;
            uint rightnode = (rulet[j] >> 1) % 2;
            // cout << j << " -- " << leftnode << rightnode << endl;
            if (leftnode != rightnode)
            {
                right_side.push(pair<int, int>(j, -1 * right_side.top().second));
            }
            else
                break;
        }
        // cout << left_side.size() << " " << right_side.size() << endl;
        while (!left_side.empty())
        {
            pair<int, int> tmp = left_side.top();
            // cout << "L: " << tmp.first << " " << tmp.second << endl;
            if (tmp.second == 1)
            {
                rulet[tmp.first] = rrotate(rulet[tmp.first]);
            }
            else
            {
                rulet[tmp.first] = lrotate(rulet[tmp.first]);
            }
            left_side.pop();
        }
        while (!right_side.empty())
        {
            pair<int, int> tmp = right_side.top();
            // cout << "R: " << tmp.first << " " << tmp.second << endl;
            if (tmp.second == 1)
            {
                rulet[tmp.first] = rrotate(rulet[tmp.first]);
            }
            else
            {
                rulet[tmp.first] = lrotate(rulet[tmp.first]);
            }
            right_side.pop();
        }
        if (action.second == 1)
            rulet[action.first] = lrotate(rulet[action.first]);
        else
            rulet[action.first] = rrotate(rulet[action.first]);
    }

    int score = 0;
    for(int i=0; i<4; i++) {
        score += (rulet[i] >> 7) * (1<<i);
    }
    cout << score << endl;
}