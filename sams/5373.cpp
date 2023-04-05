#include <iostream>
#include <string.h>
using namespace std;

enum DIRCODE
{
    FRONT = 0,
    UP = 1,
    BACK = 2,
    DOWN = 3,
    RIGHT = 4,
    LEFT = 5
};

/*
        0 1 2
        3 4 5
        6 7 8

0 1 2   0 1 2   0 1 2   0 1 2
3 4 5   3 4 5   3 4 5   3 4 5
6 7 8   6 7 8   6 7 8   6 7 8

        0 1 2
        3 4 5
        6 7 8
*/

class Face
{
public:
    char mat[3][3];
    int rcount = 0;

    Face(char color)
    {
        memset(mat, color, 9);
    }
    Face()
    {
        memset(mat, 0, 9);
    }
    void rotateFaceClockWise()
    {
        char nmat[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                nmat[j][2 - i] = mat[i][j];
            }
        }
        memcpy(mat, nmat, 9);
        rcount++;
    }

    void rotateFaceClockWiseR()
    {
        for (int i = 0; i < 3; i++)
            rotateFaceClockWise();
    }
};

Face face_arr[6];

// clockwise rotation.
void rotateUP()
{
    char copy[3];

    memcpy(copy, face_arr[FRONT].mat[0], 3);
    memcpy(face_arr[FRONT].mat[0], face_arr[RIGHT].mat[0], 3);
    memcpy(face_arr[RIGHT].mat[0], face_arr[BACK].mat[0], 3);
    memcpy(face_arr[BACK].mat[0], face_arr[LEFT].mat[0], 3);
    memcpy(face_arr[LEFT].mat[0], copy, 3);
    face_arr[UP].rotateFaceClockWise();
    return;
}

void rotateDOWN()
{
    char copy[3];

    memcpy(copy, face_arr[FRONT].mat[2], 3);
    memcpy(face_arr[FRONT].mat[2], face_arr[LEFT].mat[2], 3);
    memcpy(face_arr[LEFT].mat[2], face_arr[BACK].mat[2], 3);
    memcpy(face_arr[BACK].mat[2], face_arr[RIGHT].mat[2], 3);
    memcpy(face_arr[RIGHT].mat[2], copy, 3);
    face_arr[DOWN].rotateFaceClockWise();
    return;
}

void rotateRIGHT()
{
    char copy[3];

    face_arr[FRONT].rotateFaceClockWiseR();
    face_arr[DOWN].rotateFaceClockWiseR();
    face_arr[BACK].rotateFaceClockWise();
    face_arr[UP].rotateFaceClockWiseR();

    memcpy(copy, face_arr[FRONT].mat[0], 3);
    memcpy(face_arr[FRONT].mat[0], face_arr[DOWN].mat[0], 3); // col 2 <- col2
    memcpy(face_arr[DOWN].mat[0], face_arr[BACK].mat[0], 3);  // col 2 <- col0, reverse
    memcpy(face_arr[BACK].mat[0], face_arr[UP].mat[0], 3);    // col0, reverse <- col2
    memcpy(face_arr[UP].mat[0], copy, 3);                     // col2 <- col2

    face_arr[FRONT].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[BACK].rotateFaceClockWiseR();
    face_arr[UP].rotateFaceClockWise();

    face_arr[RIGHT].rotateFaceClockWise();
    return;
}

void rotateLEFT()
{
    char copy[3];

    face_arr[FRONT].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[BACK].rotateFaceClockWiseR();
    face_arr[UP].rotateFaceClockWise();

    memcpy(copy, face_arr[FRONT].mat[0], 3);
    memcpy(face_arr[FRONT].mat[0], face_arr[UP].mat[0], 3);  // col 0 <- col0
    memcpy(face_arr[UP].mat[0], face_arr[BACK].mat[0], 3);   // col 0 <- col2, reverse
    memcpy(face_arr[BACK].mat[0], face_arr[DOWN].mat[0], 3); // col2, reverse <- col0
    memcpy(face_arr[DOWN].mat[0], copy, 3);                  // col0 <- col0

    face_arr[FRONT].rotateFaceClockWiseR();
    face_arr[DOWN].rotateFaceClockWiseR();
    face_arr[BACK].rotateFaceClockWise();
    face_arr[UP].rotateFaceClockWiseR();

    face_arr[LEFT].rotateFaceClockWise();
    return;
}

void rotateFRONT()
{
    char copy[3];

    face_arr[LEFT].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[RIGHT].rotateFaceClockWiseR();

    memcpy(copy, face_arr[UP].mat[2], 3);
    memcpy(face_arr[UP].mat[2], face_arr[LEFT].mat[2], 3);    // row2 <- col2, reverse
    memcpy(face_arr[LEFT].mat[2], face_arr[DOWN].mat[2], 3);  // col2, reverse <- row0, reverse
    memcpy(face_arr[DOWN].mat[2], face_arr[RIGHT].mat[2], 3); // row0, reverse <- col0
    memcpy(face_arr[RIGHT].mat[2], copy, 3);                  // col0  <- row2

    face_arr[LEFT].rotateFaceClockWiseR();
    face_arr[DOWN].rotateFaceClockWiseR();
    face_arr[DOWN].rotateFaceClockWiseR();
    face_arr[RIGHT].rotateFaceClockWise();

    face_arr[FRONT].rotateFaceClockWise();
    return;
}

void rotateBACK()
{
    char copy[3];

    face_arr[RIGHT].rotateFaceClockWiseR();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[LEFT].rotateFaceClockWise();

    memcpy(copy, face_arr[UP].mat[0], 3);
    memcpy(face_arr[UP].mat[0], face_arr[RIGHT].mat[0], 3);   // row0 <- col2
    memcpy(face_arr[RIGHT].mat[0], face_arr[DOWN].mat[0], 3); // col2 <- row2, reverse
    memcpy(face_arr[DOWN].mat[0], face_arr[LEFT].mat[0], 3);  // row2, reverse <- col0, reverse
    memcpy(face_arr[LEFT].mat[0], copy, 3);                   // col0, reverse  <- row0

    face_arr[RIGHT].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[DOWN].rotateFaceClockWise();
    face_arr[LEFT].rotateFaceClockWiseR();

    face_arr[BACK].rotateFaceClockWise();
    return;
}

void rotate(char opcode[2])
{
    int rotimes = opcode[1] == '+' ? 1 : 3;

    for (int i = 0; i < rotimes; i++)
    {
        switch (opcode[0])
        {
        case 'U':
            rotateUP();
            break;
        case 'D':
            rotateDOWN();
            break;
        case 'F':
            rotateFRONT();
            break;
        case 'B':
            rotateBACK();
            break;
        case 'L':
            rotateLEFT();
            break;
        case 'R':
            rotateRIGHT();
            break;
        default:
            printf("ERROR\n");
            exit(0);
        }
    }
}

int main()
{
    int n_test;
    scanf("%d", &n_test);

    for (int test_case = 0; test_case < n_test; test_case++)
    {

        face_arr[UP] = Face('w');
        face_arr[DOWN] = Face('y');
        face_arr[FRONT] = Face('r');
        face_arr[BACK] = Face('o');
        face_arr[LEFT] = Face('g');
        face_arr[RIGHT] = Face('b');

        int N;
        char opcode[1000][2];
        string opline;
        scanf("%d", &N);
        int opidx = 0;
        while (opidx < N)
        {
            cin >> opline;
            opcode[opidx][0] = opline[0];
            opcode[opidx][1] = opline[1];
            opidx++;
        }

        for (int o = 0; o < N; o++)
        {

            rotate(opcode[o]);
            // printf("%c%c\n", opcode[o][0], opcode[o][1]);
            // for (int i = 0; i < 3; i++)
            // {
            //     for(int k=0; k<6; k++) {
            //         for (int j = 0; j < 3; j++)
            //             printf("%c", face_arr[k].mat[i][j]);
            //         printf(" ");
            //     }
            //     printf("\n");
            // }
            // printf("\n");
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                printf("%c", face_arr[UP].mat[i][j]);
            printf("\n");
        }
        // break;
    }
    return 0;
}