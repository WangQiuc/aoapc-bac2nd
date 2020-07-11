// UVa 11040 Add bricks in the wall
// wangqc
#include<iostream>

using namespace std;

int mat[9][9];
// x(0,0) = x(1,0)+x(1,1) = x(2,0)+x(2,2)+2x(2,1); x(2,1) = (x(0,0)-x(2,0)-x(2,2)) / 2
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        for(int i = 0; i <= 8; i += 2)
        {
            for(int j = 0; j <= i; j += 2)
                cin >> mat[i][j];
            if(i >= 2) for(int j = 0; j <= i-2; j += 2)
            {
                mat[i][j+1] = (mat[i-2][j]-mat[i][j]-mat[i][j+2]) / 2;
                mat[i-1][j] = mat[i][j]+mat[i][j+1];
                mat[i-1][j+1] = mat[i][j+2]+mat[i][j+1];
            }
        }
        for(int i = 0; i <= 8; i++)
        {
            for(int j = 0; j < i; j++)
                cout << mat[i][j] << " ";
            cout << mat[i][i] << endl;
        }
    }
    return 0;
}
