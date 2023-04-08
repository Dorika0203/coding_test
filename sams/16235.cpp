#include <iostream>
#include <deque>
#include <string.h>

using namespace std;

int N, M, K;
int A[10][10];
int bank[10][10];
int dead[10][10];

deque<int> view[10][10];

int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dc[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int main()
{
    cin >> N >> M >> K;
    int answer = 0;

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> A[i][j];
            bank[i][j] = 5;
        }
    }

    int tmp1, tmp2, tmp3;
    for(int i=0; i<M; i++) {
        cin >> tmp1 >> tmp2 >> tmp3;
        view[tmp1-1][tmp2-1].push_front(tmp3);
        // cout << tmp1-1  << " " << tmp2-1 << " " << tmp3 << endl;
        answer++;
    }

    for(int year=0; year<K; year++) {


        // 봄
        for(int i=0; i<10; i++) {
            for(int j=0; j<10; j++) {
                dead[i][j] = 0;

                int size = view[i][j].size();
                int remove_start_idx = size;

                for(int k=0; k<size; k++) {
                    if(bank[i][j] < view[i][j][k]) {
                        remove_start_idx = k;
                        break;
                    }
                    // cout << i << "," << j << ": ";
                    // cout << "EAT " << view[i][j][k] << " FROM " << bank[i][j] << endl;
                    bank[i][j] = bank[i][j] - view[i][j][k];
                    view[i][j][k]++;
                }
                while(size > remove_start_idx) {
                    // cout << i << "," << j << ": ";
                    // cout << "POP " << view[i][j][size-1] << " LEFT " << bank[i][j] << endl;
                    size--;
                    dead[i][j] += (view[i][j][size]/2);
                    view[i][j].pop_back();
                    answer--;
                }
            }
        }

        // 여름, 겨울
        for(int i=0; i<10; i++) {
            for(int j=0; j<10; j++) {
                bank[i][j] += dead[i][j];
                bank[i][j] += A[i][j];
            }
        }

        // 가을
        for(int i=0; i<10; i++) {
            for(int j=0; j<10; j++) {
                int n_tree = 0;
                for(int k=0; k<view[i][j].size(); k++) {
                    if(view[i][j][k] %5 != 0) continue;
                    n_tree++;
                }
                if(n_tree != 0) {
                    // cout << i << "," << j << ": ";
                    // cout << "ADD " << n_tree << endl;
                }
                for(int dir=0; dir<8; dir++) {
                    int nr = i + dr[dir];
                    int nc = j + dc[dir];
                    if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1) continue;
                    for(int cnt=0; cnt<n_tree; cnt++) {
                        view[nr][nc].push_front(1);
                    }
                    answer += n_tree;
                }
            }
        }

        // break;
    }
    cout << answer << endl;

}