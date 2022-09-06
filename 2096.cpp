// 내려가기, 슬라이딩 윈도우, DP

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

uint32_t buffer[3];
uint32_t minbuff[2][3];
uint32_t maxbuff[2][3];

int main()
{
    int N;
    cin >> N;

    for(int i=0; i<N; i++)
    {
        cin >> buffer[0] >> buffer[1] >> buffer[2];
        minbuff[1][0] = min(minbuff[0][0], minbuff[0][1]) + buffer[0];
        minbuff[1][1] = min(min(minbuff[0][0], minbuff[0][1]), minbuff[0][2]) + buffer[1];
        minbuff[1][2] = min(minbuff[0][1], minbuff[0][2]) + buffer[2];

        minbuff[0][0] = minbuff[1][0];
        minbuff[0][1] = minbuff[1][1];
        minbuff[0][2] = minbuff[1][2];

        maxbuff[1][0] = max(maxbuff[0][0], maxbuff[0][1]) + buffer[0];
        maxbuff[1][1] = max(max(maxbuff[0][0], maxbuff[0][1]), maxbuff[0][2]) + buffer[1];
        maxbuff[1][2] = max(maxbuff[0][1], maxbuff[0][2]) + buffer[2];

        maxbuff[0][0] = maxbuff[1][0];
        maxbuff[0][1] = maxbuff[1][1];
        maxbuff[0][2] = maxbuff[1][2];
    }

    int maxval = max(max(maxbuff[0][0], maxbuff[0][1]), maxbuff[0][2]);
    int minval = min(min(minbuff[0][0], minbuff[0][1]), minbuff[0][2]);

    cout << maxval << " " << minval << endl;
}