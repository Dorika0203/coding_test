#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> loc;
typedef pair<int, char> turn;
typedef unsigned int uint;

int view[102][102];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
    int N, K, L;
    cin >> N >> K;
    vector<loc> apples;
    queue<turn> turns;
    queue<loc> snake;

    int second = 1;
    int dir = 0;

    for (int i = 0; i < K; i++)
    {
        int a, b;
        cin >> a >> b;
        apples.push_back(loc(a, b));
        view[a][b] = 2;
    }
    cin >> L;
    for (int i = 0; i < L; i++)
    {
        int a;
        char b;
        cin >> a >> b;
        turns.push(turn(a, b));
    }

    snake.push(loc(1, 1));
    view[1][1] = -1;

    while (true)
    {

        loc head = snake.back();
        loc newhead = loc(head.first + dy[dir], head.second + dx[dir]);
        // cout << second << " : " << newhead.first << ", " << newhead.second << endl;
        if (newhead.first == 0 || newhead.first == N + 1 || newhead.second == 0 || newhead.second == N + 1)
            break;
        if (view[newhead.first][newhead.second] == -1)
            break;

        loc tail = snake.front();
        view[tail.first][tail.second] = 0;

        if (view[newhead.first][newhead.second] != 2)
        {
            loc tail = snake.front();
            view[tail.first][tail.second] = 0;
            snake.pop();
        }

        view[newhead.first][newhead.second] = -1;
        snake.push(newhead);
        if (second == turns.front().first)
        {
            dir = turns.front().second == 'D' ? (dir + 1) % 4 : (dir + 3) % 4;
            turns.pop();
        }
        second++;
    }
    cout << second << endl;
}