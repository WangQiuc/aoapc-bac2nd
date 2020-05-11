// UVa215 Spreadsheet Calculator
// wangqc

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cctype>

using namespace std;

const int maxr = 22, maxc = 12;
int n, m, vis[maxr][maxc], sheet[maxr][maxc];
string expr[maxr][maxc];

bool dfs(int x0, int y0)
{
    vis[x0][y0] = -1;
    string s = expr[x0][y0];
    int val = 0, i = 0, sign = 1, n = s.length();
    while (i < n)
    {
        if (s[i] == '+') {i++; sign = 1;}
        else if (s[i] == '-') {i++; sign = -1;}
        else if (isdigit(s[i]))
        {
            int t = 0;
            while(i < n && isdigit(s[i]))
                t = t * 10 + (s[i++]-'0');
            val += sign * t;
        }
        else
        {
            int x = s[i++]-'A', y = s[i++]-'0';
            if (vis[x][y] == -1 || (!vis[x][y] && !dfs(x, y))) return false;
            val += sign * sheet[x][y];
        }
    }
    vis[x0][y0] = 1, sheet[x0][y0] = val;
    return true;
}

int main()
{
    while (cin >> n >> m && n)
    {
        string s;
        memset(vis, 0, sizeof(vis));
        memset(sheet, 0, sizeof(sheet));
        memset(expr, 0, sizeof(expr));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> s;
                expr[i][j] = s;
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!vis[i][j]) dfs(i, j);
        bool loop = false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (vis[i][j] == -1)
                {
                    loop = true;
                    printf("%c%d: ", i + 'A', j);
                    cout << expr[i][j] << endl;
                }
        if (!loop)
        {
            cout << " ";
            for (int j = 0; j < m; j++) printf("%6d", j);
            cout << endl;
            for (int i = 0; i < n; i++)
            {
                printf("%c", i + 'A');
                for (int j = 0; j < m; j++) printf("%6d", sheet[i][j]);
                cout << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
