// UVa 10618 Tango Tango Insurrection
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int U = 0, L = 1, R = 2, D = 3;
const int maxn = 75;

// d[i][a][b][s] ith steps L foot on a, R foot on b, move s (0-no move, 1-L move, 2-R move)
int d[maxn][4][4][3], path[maxn][4][4][3];

char seq[maxn], pos[256], foot[] = ".LR";

int energy(int x0, int x)       // action from x0 to x
{
    if (x == x0) return 3;
    if (x + x0 == 3) return 7;
    return 5;
}

int energy(int i, int a0, int b0, int s, int f, int x, int &a, int &b)
{
    a = a0, b = b0;
    if (f == 1) a = x;
    else if (f == 2) b = x;
    if (a == b || (a == R && b == L)) return -1;
    // can't move L/R foot before R/L comes back
    if ((a0 == R && b != b0) || (b0 == L && a != a0)) return -1;
    if (f == 0) return 0;
    if (f != s) return 1;
    if (f == 1) return energy(a0, a);
    return energy(b0, b);
}

// foot f move to arrow x
void move(int i, int a0, int b0, int s, int f, int x)
{
    int a, b, e;
    if ((e = energy(i, a0, b0, s, f, x, a, b)) < 0) return;
    int &ans = d[i][a0][b0][s];
    int cost = d[i+1][a][b][f] + e;
    if (cost < ans) ans = cost, path[i][a0][b0][s] = (f << 2) | x;
}

int main()
{
    pos['U'] = 0, pos['L'] = 1, pos['R'] = 2, pos['D'] = 3;
    while(cin >> seq && seq[0] != '#')
    {
        int n = strlen(seq);
        memset(d, 0, sizeof(d));
        for (int i = n-1; i >= 0; i--)
            for (int a = 0; a < 4; a++)
                for (int b = 0; b < 4; b++) if (a != b)
                    for (int s = 0; s < 3; s++)
                    {
                        d[i][a][b][s] = 10 * n;
                        if (seq[i] == '.')
                        {
                            move(i, a, b, s, 0, 0);
                            for (int x = 0; x < 4; x++)
                            {
                                move(i, a, b, s, 1, x);
                                move(i, a, b, s, 2, x); 
                            }
                        }
                        else 
                        {
                            move(i, a, b, s, 1, pos[seq[i]]);
                            move(i, a, b, s, 2, pos[seq[i]]);
                        }
                    }
        int a = L, b = R, s = 0;
        for (int i = 0; i < n; i++)
        {
            int f = path[i][a][b][s] >> 2, x = path[i][a][b][s] & 3;
            cout << foot[f];
            s = f;
            if (f == 1) a = x;
            else if (f == 2) b = x;
        }
        cout << endl;
    }
    return 0;
}
