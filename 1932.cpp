// 정수 삼각형, DP

#include <cstdio>
#include <algorithm>

int map[500][500];
int score[500][500];

using namespace std;

int main()
{
    int N;
    scanf("%d", &N);
    

    for(int i=0; i<N; i++) {
        for(int j=0; j<i+1; j++) {
            scanf("%d", map[i]+j);
        }
    }

    score[0][0] = map[0][0];
    
    for(int i=1; i<N; i++) {
        score[i][0] = score[i-1][0] + map[i][0];
        score[i][i] = score[i-1][i-1] + map[i][i];

        for(int j=1; j<i; j++) {
            score[i][j] = max(score[i-1][j-1], score[i-1][j]) + map[i][j];
        }
    }

    int max = score[N-1][0];
    for(int i=1; i<N; i++) {
        if(score[N-1][i] > max)
            max = score[N-1][i];
    }

    printf("%d\n", max);
}