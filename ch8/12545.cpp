// UVa 12545 Bits Equalizer
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

string s1, s2;

int solve()
{
    int n = s1.length(), c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++)
        c1 += s1[i] == '1', c2 += s2[i] == '1';
    if (c1 > c2) return -1;
    c1 = 0;
    for (int i = 0; i < n; i++) if (s1[i] != s2[i] && s1[i] != '?')
        for (int j = i+1; j < n; j++) if (s1[j] == s2[i] && s1[i] == s2[j])
        {
            c1++;
            swap(s1[i], s1[j]);
            break;
        }
    for (int i = 0; i < n; i++)
        c1 += s1[i] != s2[i];
    return c1;
}

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> s1 >> s2;
        cout << "Case " << kase << ": " << solve() << endl;
    }
    return 0;
}
