// RGB 거리

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N = 0;
    cin>>N;
    vector<vector<int>> cost_mat(N, vector<int>(N));
    vector<vector<int>> score_mat(N, vector<int>(N));

    // score_mat(i, j) -> i번째 집까지의 최소비용 값, i번째 집의 색이 j일때 (RGB, 0~2)
    score_mat[0][0] = cost_mat[0][0];
    score_mat[0][1] = cost_mat[0][1];
    score_mat[0][2] = cost_mat[0][2];

    for(int i=1; i<N; i++) {
        score_mat[i][0] = cost_mat[i][0] + min(score_mat[i-1][1], score_mat[i-1][2]);
        score_mat[i][1] = cost_mat[i][1] + min(score_mat[i-1][0], score_mat[i-1][2]);
        score_mat[i][2] = cost_mat[i][2] + min(score_mat[i-1][0], score_mat[i-1][1]);
    }

    int score = min(score_mat[N-1][0], min(score_mat[N-1][1], score_mat[N-1][2]));

    cout<<score;
    return 0;
}