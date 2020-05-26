// UVa 1442 Cave
// wangqc
#include<iostream>

using namespace std;

const int maxn = 1000005;
int p[maxn], s[maxn], h[maxn];

int main()
{
    int n, T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> s[i];
        h[0] = s[0];
        for (int i = 1; i < n; i++)
            h[i] = max(min(h[i-1], s[i]), p[i]);
        int cnt = 0, level = s[n-1];
        for (int i = n-1; i >= 0; i--)
        {
            level = max(min(level, s[i]), p[i]);
            cnt += min(level, h[i]) - p[i];
        }
        cout << cnt << endl;
    }
    return 0;
}
