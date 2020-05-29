// UVa 1610 Party Games
// wangqc
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string s[1000];

string solve(string a, string b)  // find shortest then smallest c that a <= c < b
{
    int i = 0, n = a.length();
    string c = "A";
    while (i < n)
    {
        while (c[i] < 'Z' && c < a) c[i]++;  // if |c| <= |a|, c[i] = a[i]+1 or 'z'
        if (a <= c && c < b) break;
        if (a[i] != c[i]) c[i]--;
        c += 'A', i++;
    }
    return c;
}

int main()
{
    int n;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++) cin >> s[i];
        sort(s, s+n);
        cout << solve(s[(n>>1)-1], s[n>>1]) << endl;
    }
    return 0;
}
