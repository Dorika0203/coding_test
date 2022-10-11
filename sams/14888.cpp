#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    int opcounts[4];
    cin >> N;

    int *nums = new int[N];
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
    for (int i = 0; i < 4; i++)
    {
        cin >> opcounts[i];
    }

    int* oparr = new int[N-1];
    int min = 0x7fffffff;
    int max = 0x80000000;

    int max_bitmap = 4 << 2*(N - 2);

    int plus, minus, mult, div;
    for (int bitmap = 0; bitmap < max_bitmap; bitmap++) {
        plus = minus = mult = div = 0;
        int tmp = bitmap;
        bool flag = true;
        for (int j = 0; j < N - 1; j++) {
            int i = tmp % 4;
            switch (i) {
            case 1:
                minus++;
                oparr[j] = 1;
                break;
            case 2:
                mult++;
                oparr[j] = 2;
                break;
            case 3:
                div++;
                oparr[j] = 3;
                break;
            default:
                plus++;
                oparr[j] = 0;
                break;
            }
            tmp = tmp / 4;
        }
        if (plus != opcounts[0] || minus != opcounts[1] || mult != opcounts[2] || div != opcounts[3])
            continue;
        tmp = nums[0];
        for (int i = 0; i < N - 1; i++) {
            switch (oparr[i])
            {
            case 1:
                tmp -= nums[i+1];
                break;
            case 2:
                tmp *= nums[i+1];
                break;
            case 3:
                tmp /= nums[i+1];
                break;
            default:
                tmp += nums[i+1];
                break;
            }
        }
        max = max > tmp ? max : tmp;
        min = min < tmp ? min : tmp;
    }

    cout << max << endl << min << endl;
    return 0;
}