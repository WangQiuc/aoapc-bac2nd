// UVa 11214 Guarding the Chessboard
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

vector<int> mark;
bool cover[4][20];  // covered from 4 directions
int n, m, maxd;

bool check()
{
    for (int x : mark)
    {
        int i = x / n, j = x % n;
        if (!(cover[0][i] || cover[1][j] || cover[2][i+j]|| cover[3][i-j+n])) 
            return false;
    }
    return true;
}

bool dfs(int d, int p)      // start search from ith row
{
    if (d == maxd) return check();
    for (; p < n * m; p++)
    {
        int i = p / n, j = p % n;
        if (!(cover[0][i] && cover[1][j] && cover[2][i+j] && cover[3][i-j+m]))
        {
            bool b0 = cover[0][i], b1 = cover[1][j], b2 = cover[2][i+j], b3 = cover[3][i-j+n];
            cover[0][i] = cover[1][j] = cover[2][i+j] = cover[3][i-j+n] = true;
            if (dfs(d+1, p+1)) return true;
            cover[0][i] = b0, cover[1][j] = b1, cover[2][i+j] = b2, cover[3][i-j+n] = b3;
        }
    }
    return false;
}

int main()
{
    char c;
    int kase = 0;
    while (cin >> n >> m && n)
    {
        mark.clear();
        memset(cover, 0, sizeof(cover));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (cin >> c && c == 'X') mark.push_back(i*n+j);
        for (maxd = 0; maxd < 5 ; maxd++)
            if (dfs(0, 0)) break;
        cout << "Case " << ++kase << ": " << maxd << endl; 
    }
    return 0;
}
