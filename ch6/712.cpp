// UVa712 S-Trees
// wangqc

#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 130;     // 2^7
int idx[maxn];

int main()
{
    int n, m, kase = 0;
    string s, s2;
    while (cin >> n && n)
    {
        cout << "S-Tree #" << ++kase << ":\n";
        for (int i = 0; i < n; i++)
        {
            cin >> s;
            int j = s[1] - '1';
            idx[j] = i;
        }
        cin >> s >> m;
        while (m--)
        {
            int q[n];
            cin >> s2;
            for (int i = 0; i < n; i++)
                q[idx[i]] = s2[i] - '0';
            int lo = 0, hi = (1 << n) - 1;
            for (int i : q)
            {
                if (i) lo = (lo + hi + 1) >> 1;
                else hi = (lo + hi) >> 1;
            }
            cout << s[lo];
        }
        cout << endl << endl;
    }
    return 0;
}
