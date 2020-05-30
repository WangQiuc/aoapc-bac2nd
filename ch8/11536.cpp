// UVa 11536 Smallest Sub-Array
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1000005;
int n, m, k, a[maxn], v[maxn];

void init()
{
    memset(a, 0, sizeof(a));
    memset(v, 0, sizeof(v));
    a[0] = 1, a[1] = 2, a[2] = 3;
    for (int i = 3; i < n; i++)
        a[i] = (a[i-3] + a[i-2] + a[i-1]) % m + 1;
}

bool solve()
{
    int L = 0, R = 0, cnt = 0, minlen = n + 1;
    while (R < n)
    {
        int x = a[R++];
        cnt += (x <= k && v[x]++ == 0);
        while (cnt == k)
        {
            minlen = min(minlen, R-L);
            x = a[L++];
            cnt -= (x <= k && --v[x] == 0);
        }
    }
    if (minlen == n+1) return false;
    cout << minlen << endl;
    return true;
}

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> n >> m >> k;
        init();
        cout << "Case " << kase << ": ";
        if (!solve()) cout << "sequence nai\n";
    }
    return 0;
}
