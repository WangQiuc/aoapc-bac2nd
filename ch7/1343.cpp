// UVa
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

/*
      00    01
      02    03
04 05 06 07 08 09 10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/

int line[8][7] = 
{
    {0, 2, 6, 11, 15, 20, 22},      // A
    {1, 3, 8, 12, 17, 21, 23},      // B
    {10, 9, 8, 7, 6, 5, 4},         // C
    {19, 18, 17, 16, 15, 14, 13}    // D
};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};
int a[24];
char seq[1000];     // sequence of steps

bool is_target()
{
    int symbol = a[center[0]];
    for (int i = 1; i <= 7; i++)
        if (a[center[i]] != symbol) return false;
    return true;
}

int diff(int symbol)
{
    int cnt = 0;
    for (int i : center)
        cnt += a[i] != symbol;
    return cnt;  
}

int h() { return min(min(diff(1), diff(2)), diff(3)); }

void move(int i)
{
    int t = a[line[i][0]];
    for (int j = 0; j < 6; j++)
        a[line[i][j]] = a[line[i][j+1]];
    a[line[i][6]] = t;
}

bool dfs(int d, int maxd)
{
    if (is_target()) 
    {
        seq[d] = '\0';
        cout << seq << endl;
        return true;
    }
    if (d + h() > maxd) return false;
    for (int i = 0; i < 8; i++)
    {
        seq[d] = 'A' + i;
        move(i);
        if (dfs(d + 1, maxd)) return true;
        move(rev[i]);
    }
    return false;
}

int main()
{
    for (int i = 4; i < 8; i++)
        for (int j = 0; j <= 6; j++)
            line[i][j] = line[rev[i]][6-j];
    while( cin >> a[0] && a[0])
    {
        for (int i = 1; i < 24; i++) cin >> a[i];
        if (is_target()) cout << "No moves needed\n";
        else
        {
            for (int maxd = 1; ; maxd++)
                if (dfs(0, maxd)) break;
        }
        cout << a[center[0]] << endl;
    }
    return 0;
}
