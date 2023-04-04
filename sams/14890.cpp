#include <stdio.h>
#include <stack>

using namespace std;

int N, L;
int view[100][100];

int main()
{
    scanf("%d %d", &N, &L);
    int ans = 2 * N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &view[i][j]);
        }
    }


    // solve rows
    // printf("SOLVE_ROWS\n");
    for (int i = 0; i < N; i++)
    {
        // printf("[%d]\n", i);
        int prev = view[i][0];
        int prev_counter = 1;
        int next_low_counter = 0;
        int j = 1;
        while (j < N)
        {
            // same
            if (view[i][j] == prev) {
                prev_counter++;
            }
            // higher
            else if (view[i][j] > prev) {
                // printf("HIGHER %d\n", j);
                if (view[i][j] != prev+1 || prev_counter < L) {
                    // printf("FAIL %d %d\n", j, prev_counter);
                    ans--;
                    break;
                }
                prev = view[i][j];
                prev_counter = 1;
            }
            // lower
            else {
                // printf("LOWER %d\n", j);
                if (view[i][j] != prev-1) {
                    // printf("TOO LOW FAIL\n");
                    ans--;
                    break;
                }
                int k = 0;
                while(j+k < N && view[i][j+k] == view[i][j] && next_low_counter < L) {
                    next_low_counter++;
                    // printf("LOW COUNT = %d, %d\n", next_low_counter, j+k);
                    k++;
                }
                if(next_low_counter < L) {
                    // printf("NOW ENOUGH LOW FAIL\n");
                    ans--;
                    break;
                }
                prev = view[i][j+k-1];
                prev_counter=0;
                next_low_counter=0;
                j = j+k-1;
            }
            j++;
        }
    }

    // printf("SOLVE_COLS\n");
    // solve cols
    for (int i = 0; i < N; i++)
    {
        // printf("[%d]\n", i);
        int prev = view[0][i];
        int prev_counter = 1;
        int next_low_counter = 0;
        int j = 1;
        while (j < N)
        {
            // same
            if (view[j][i] == prev) {
                prev_counter++;
            }
            // higher
            else if (view[j][i] > prev) {
                // printf("HIGHER %d\n", j);
                if (view[j][i] != prev+1 || prev_counter < L) {
                    // printf("FAIL %d %d\n", j, prev_counter);
                    ans--;
                    break;
                }
                prev = view[j][i];
                prev_counter = 1;
            }
            // lower
            else {
                // printf("LOWER %d\n", j);
                if (view[j][i] != prev-1) {
                    // printf("TOO LOW FAIL\n");
                    ans--;
                    break;
                }
                int k = 0;
                while(j+k < N && view[j+k][i] == view[j][i] && next_low_counter < L) {
                    next_low_counter++;
                    // printf("LOW COUNT = %d, %d\n", next_low_counter, j+k);
                    k++;
                }
                if(next_low_counter < L) {
                    // printf("NOW ENOUGH LOW FAIL\n");
                    ans--;
                    break;
                }
                prev = view[j+k-1][i];
                prev_counter=0;
                next_low_counter=0;
                j = j+k-1;
            }
            j++;
        }
    }

    printf("%d\n", ans);
}