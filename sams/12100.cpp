#include <iostream>
#include <vector>

using namespace std;

int N;
int view[20][20];
typedef struct pair<int, bool> fint;

void print_board(int cview[20][20]) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", cview[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void move_board(int dir, int cview[20][20])
{
    vector<fint> nline;
    // print_board(cview);

    if (dir < 2)
    {
        // printf("1111\n");
        // (west, east)
        for (int i = 0; i < N; i++)
        {
            nline.clear();
            // cout << "I: " << i << endl;
            int j = dir % 2 == 0 ? 0 : N - 1;
            int dj = dir % 2 == 0 ? 1 : -1;
            while (j > -1 && j < N)
            {
                if (cview[i][j] == 0) {
                    j+=dj;
                    continue;
                }
                if (!nline.empty() && nline.back().first == cview[i][j] && nline.back().second)
                {
                    // cout << "MERGE" << endl;
                    nline.pop_back();
                    nline.push_back(fint(cview[i][j] * 2, false));
                }
                else
                {
                    // cout << "PUSH" << endl;
                    nline.push_back(fint(cview[i][j], true));
                }
                j += dj;
            }
            j = dir % 2 == 0 ? 0 : N - 1;
            dj = dir % 2 == 0 ? 1 : -1;
            for (int k = 0; k < N; k++)
            {
                cview[i][j + dj * k] = k < nline.size() ? nline[k].first : 0;
            }
        }
    }
    else
    {
        // (north, south)
        for (int i = 0; i < N; i++)
        {
            nline.clear();
            int j = dir % 2 == 0 ? 0 : N - 1;
            int dj = dir % 2 == 0 ? 1 : -1;
            while (j > -1 && j < N)
            {
                if (cview[j][i] == 0) {
                    j+=dj;
                    continue;
                }
                if (!nline.empty() && nline.back().first == cview[j][i] && nline.back().second)
                {
                    nline.pop_back();
                    nline.push_back(fint(cview[j][i] * 2, false));
                }
                else
                    nline.push_back(fint(cview[j][i], true));
                j += dj;
            }
            j = dir % 2 == 0 ? 0 : N - 1;
            dj = dir % 2 == 0 ? 1 : -1;
            for (int k = 0; k < N; k++)
            {
                cview[j + dj * k][i] = k < nline.size() ? nline[k].first : 0;
            }
        }
    }
    // print_board(cview);
    return;
}


int solve(int dir, int count, int pview[20][20])
{
    // printf("%d, %d\n", dir, count);
    int max = -1;

    // cpy
    int cview[20][20];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cview[i][j] = pview[i][j];
        }
    }
    // printf("COPY DONE\n");
    // move
    move_board(dir, cview);

    // was last move
    if (count == 4)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                max = max > cview[i][j] ? max : cview[i][j];
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            int retval = solve(i, count + 1, cview);
            max = max < retval ? retval : max;
        }
    }
    return max;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &view[i][j]);
        }
    }
    // printf("FUCK\n");
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        // if(i != 1) continue;
        int retval = solve(i, 0, view);
        ans = ans > retval ? ans : retval;
    }
    printf("%d\n", ans);
}