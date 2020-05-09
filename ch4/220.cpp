// UVa220 Othello
// wangqc

#include <iostream>
using namespace std;

char p1, p2, board[10][10];
int ok;

int valid(int r, int c)
{
    return r >= 1 && r <= 8 && c >= 1 && c <= 8;
}

void move(int r, int c, int list)
{
    for (int i = -1; i <= 1; i++)       // eight neighbor slots
        for (int j = -1; j <= 1; j++)
        {
            if (!i && !j) continue;     // skip itself
            int x = r + i, y = c + j;
            while (valid(x, y) && board[x][y] == p2) 
                x += i, y += j;   
            if (board[x][y] == p1 && (x != r + i || y != c + j))
            {
                if (list)
                {
                    if (ok++) printf(" ");
                    printf("(%d,%d)", r, c);
                    return;
                }
                else
                    for (; x != r - i || y != c - j; x -= i, y -= j)
                        board[x][y] = p1;
            }
        }
}

int main()
{
    int T;
    cin >> T;
    while (T)
    {
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                cin >> board[i][j];
        cin >> p1;
        char cmd;
        while (cin >> cmd && cmd != 'Q')
        {
            p2 = p1 == 'W' ? 'B' : 'W';
            if (cmd == 'L')
            {
                ok = 0;
                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j <= 8; j++)
                        if (board[i][j] == '-')
                            move(i, j, 1);
                if (!ok) 
                {
                    cout << "No legal move."; 
                    p1 = p1 == 'W' ? 'B' : 'W';
                }
                cout << endl;
            }
            else
            {
                int ij;
                cin >> ij;
                move(ij/10, ij%10, 0);
                int wcnt = 0, bcnt = 0;
                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j <= 8; j++)
                    {
                        if (board[i][j] == 'B') bcnt++;
                        else if (board[i][j] == 'W') wcnt++;
                    }
                printf("Black -%3d White -%3d\n", bcnt, wcnt);
                p1 = p1 == 'W' ? 'B' : 'W';
            }
            
        }
        for (int i = 1; i <= 8; i++)
        {
            for (int j = 1; j <= 8; j++)
                cout << board[i][j];
            cout << endl;
        }
        if (--T) cout << endl;
    }
    return 0;
}
