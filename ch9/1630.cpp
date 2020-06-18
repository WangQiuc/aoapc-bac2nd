// UVa 1630 Folding
// wangqc
#include<iostream>
#include<string>

using namespace std;

const int maxn = 105;

string sub[maxn][maxn];
int n;

int get_pattern_len(string S, int n)
{
    int dfa[n+1] = {0};
    for (int i = 1; i < n; i++)
    {
        int j = dfa[i];
        while (j && S[i] != S[j]) 
            j = dfa[j];
        dfa[i+1] = S[i]==S[j] ? j+1 : 0;
    }
    return dfa[n] && !(n % (n-dfa[n])) ? n-dfa[n] : 0;
}

int main()
{
    string s;
    while (cin >> s)
    {
        int n = s.length();
        for (int i = 0; i < n; i++)
            sub[i][i] = s[i];
        for (int d = 2; d <= n; d++)    // length of substring
            for (int i = 0; i <= n-d; i++)
            {
                int j = i+d-1;
                sub[i][j] = s.substr(i, d);
                int p = get_pattern_len(sub[i][j], d);
                if (p)
                {
                    string t = to_string(d/p) + '(' + sub[i][i+p-1] + ')';
                    if (t.length() < sub[i][j].length()) sub[i][j] = t;
                }
                for (int k = i; k < j; k++)
                    if (sub[i][k].length() + sub[k+1][j].length() < sub[i][j].length())
                        sub[i][j] = sub[i][k] + sub[k+1][j];
            }
        cout << sub[0][n-1] << endl;
    }
    return 0;
}
