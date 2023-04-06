#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct pair<int, int> coord;

class CCTV
{
public:
    int type;
    coord loc;

    CCTV()
    {
        type = -1;
        loc = coord(-1, -1);
    }

    CCTV(int _type, coord _loc)
    {
        type = _type;
        loc = _loc;
    }
};

class Sim
{
public:
    char sview[8][8];
    int nn, remains;
    Sim() {}
};

char view[8][8];
CCTV cctv_arr[8];
int n, N, M;

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

int dlist2[2] = {0, 2};
int dlist3[2] = {0, 1};
int dlist4[3] = {0, 1, 2};

void print_view(char vv[8][8])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d ", vv[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    cin >> N >> M;
    n = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> view[i][j];
            view[i][j] -= '0';
            if (view[i][j] > 0 && view[i][j] < 6)
            {
                cctv_arr[n] = CCTV(view[i][j], coord(i, j));
                n++;
            }
        }
    }

    Sim start;
    start.remains = N * M;
    start.nn = n;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            start.sview[i][j] = view[i][j];
            if (start.sview[i][j] == 6)
                start.remains--;
        }
    }

    stack<Sim> task;
    task.push(start);
    int ans = start.remains;
    if(n==0) task.pop();
    
    while (!task.empty())
    {
        if (ans == 0)
            break;
        Sim curSim = task.top();
        task.pop();
        curSim.nn--;
        int ttype = cctv_arr[curSim.nn].type;
        coord tloc = cctv_arr[curSim.nn].loc;
        int nr, nc, mult;

        // printf("--------- %d %d %d,%d -----------------\n",curSim.nn, ttype, tloc.first, tloc.second);
        switch (ttype)
        {
        case 1:
            for (int dir = 0; dir < 4; dir++)
            {
                // printf("------------------ %d ------\n", dir);
                Sim newSim = curSim;
                mult = 0;
                while (true)
                {
                    nr = tloc.first + mult * dr[dir];
                    nc = tloc.second + mult * dc[dir];
                    if (nr < 0 || nr > N - 1 || nc < 0 || nc > M - 1)
                        break;
                    if (newSim.sview[nr][nc] == 6)
                        break;
                    if (newSim.sview[nr][nc] != 7)
                        newSim.remains--;
                    newSim.sview[nr][nc] = 7;
                    // print_view(newSim.sview);
                    mult++;
                }
                if (newSim.nn == 0)
                {
                    ans = ans > newSim.remains ? newSim.remains : ans;
                }
                else
                    task.push(newSim);
            }
            break;
        case 2:
            for (int dir = 0; dir < 2; dir++)
            {
                // // printf("------------------ %d ------\n", dir);
                Sim newSim = curSim;
                for (int idx = 0; idx < 2; idx++)
                {
                    mult = 0;
                    while (true)
                    {
                        nr = tloc.first + mult * dr[(dir + dlist2[idx]) % 4];
                        nc = tloc.second + mult * dc[(dir + dlist2[idx]) % 4];
                        if (nr < 0 || nr > N - 1 || nc < 0 || nc > M - 1)
                            break;
                        if (newSim.sview[nr][nc] == 6)
                            break;
                        if (newSim.sview[nr][nc] != 7)
                            newSim.remains--;
                        newSim.sview[nr][nc] = 7;
                        // print_view(newSim.sview);
                        mult++;
                    }
                }
                if (newSim.nn == 0)
                {
                    ans = ans > newSim.remains ? newSim.remains : ans;
                }
                else
                    task.push(newSim);
            }
            break;
        case 3:
            for (int dir = 0; dir < 4; dir++)
            {
                // // printf("------------------ %d ------\n", dir);
                Sim newSim = curSim;
                for (int idx = 0; idx < 2; idx++)
                {
                    mult = 0;
                    while (true)
                    {
                        nr = tloc.first + mult * dr[(dir + dlist3[idx]) % 4];
                        nc = tloc.second + mult * dc[(dir + dlist3[idx]) % 4];
                        if (nr < 0 || nr > N - 1 || nc < 0 || nc > M - 1)
                            break;
                        if (newSim.sview[nr][nc] == 6)
                            break;
                        if (newSim.sview[nr][nc] != 7)
                            newSim.remains--;
                        newSim.sview[nr][nc] = 7;
                        // print_view(newSim.sview);
                        mult++;
                    }
                }
                if (newSim.nn == 0)
                {
                    ans = ans > newSim.remains ? newSim.remains : ans;
                }
                else
                    task.push(newSim);
            }
            break;
        case 4:
            for (int dir = 0; dir < 4; dir++)
            {
                // // printf("------------------ %d ------\n", dir);
                Sim newSim = curSim;
                for (int idx = 0; idx < 3; idx++)
                {
                    mult = 0;
                    while (true)
                    {
                        nr = tloc.first + mult * dr[(dir + dlist4[idx]) % 4];
                        nc = tloc.second + mult * dc[(dir + dlist4[idx]) % 4];
                        if (nr < 0 || nr > N - 1 || nc < 0 || nc > M - 1)
                            break;
                        if (newSim.sview[nr][nc] == 6)
                            break;
                        if (newSim.sview[nr][nc] != 7)
                            newSim.remains--;
                        newSim.sview[nr][nc] = 7;
                        // print_view(newSim.sview);
                        mult++;
                    }
                }
                if (newSim.nn == 0)
                {
                    ans = ans > newSim.remains ? newSim.remains : ans;
                }
                else
                    task.push(newSim);
            }
            break;
        case 5:
            {
                Sim newSim = curSim;
                for (int idx = 0; idx < 4; idx++)
                {
                    mult = 0;
                    while (true)
                    {
                        nr = tloc.first + mult * dr[idx];
                        nc = tloc.second + mult * dc[idx];
                        if (nr < 0 || nr > N - 1 || nc < 0 || nc > M - 1)
                            break;
                        if (newSim.sview[nr][nc] == 6)
                            break;
                        if (newSim.sview[nr][nc] != 7)
                            newSim.remains--;
                        newSim.sview[nr][nc] = 7;
                        // print_view(newSim.sview);
                        mult++;
                    }
                }
                if (newSim.nn == 0)
                {
                    ans = ans > newSim.remains ? newSim.remains : ans;
                }
                else
                    task.push(newSim);
            }
            break;
        default:
            printf("ERRORCODE %d\n", ttype);
        }
    }

    printf("%d\n", ans);
}