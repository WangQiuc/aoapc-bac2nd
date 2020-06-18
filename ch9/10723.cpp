// UVa 10723 Cyborg Genes
// wangqc
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

const int maxn = 35;
int d[maxn][maxn], f[maxn][maxn];

void init()
{
    memset(d, 0, sizeof(d));
    memset(f, 0, sizeof(f));
    for (int i = 0; i < maxn; i++)
        d[i][0] = d[0][i] = i, f[i][0] = f[0][i] = 1;
}

int main()
{
    string s, t;
    int T;
    cin >> T;
    getchar();
    for (int kase = 1; kase <= T; kase++)
    {
        init();
        getline(cin, s);
        getline(cin, t);
        int n = s.length(), m = t.length();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                d[i+1][j+1] = (s[i]==t[j] ? d[i][j] : min(d[i][j+1], d[i+1][j])) + 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (s[i]==t[j]) f[i+1][j+1] = f[i][j];
                else f[i+1][j+1] = f[i][j+1]*(d[i][j+1]<=d[i+1][j]) + f[i+1][j]*(d[i][j+1]>=d[i+1][j]);
            }
        cout << "Case #" << kase << ": " << d[n][m] << " " << f[n][m] << endl;
    }
    return 0;
}
