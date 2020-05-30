// UVa 1619 Feel Good
// wangqc
#include<iostream>
#include<cstring>

const int maxn = 100005;
typedef long long LL;
int n, a[maxn], l[maxn], r[maxn];   // the minimum of range [l[i], r[i]] is a[i]
LL s[maxn];

using namespace std;

int main()
{
    int kase = 0;
    a[0] = -1, s[0] = 0;
    while (cin >> n && n)
    {
        a[n+1] = -1;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            s[i] = s[i-1] + a[i];
            l[i] = r[i] = i;
        }
        for (int i = 1; i <= n; i++)
            while (a[i] <= a[l[i]-1]) 
                l[i] = l[l[i]-1];
        for (int i = n; i >= 1; i--)
            while (a[i] <= a[r[i]+1]) 
                r[i] = r[r[i]+1];
        LL maxv = (LL)a[1]*a[1];
        int L = 1, R = 1;
        for (int i = 1; i <= n; i++)
        {
            LL v = (s[r[i]]-s[l[i]-1]) * a[i];
            if (v > maxv) maxv = v, L = l[i], R = r[i];
        }
        if (kase++) cout << endl;
        cout << maxv << endl << L << " " << R << endl;
    }
    return 0;
}
