// UVa 714 Copying Books
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

typedef long long LL;

const int maxn = 505;
int m, k, a[maxn];
bool divider[maxn];        // last book assigned to a scribe

bool solve(long long x)
{
    long long agg = 0;
    int cnt = 1;
    for (int i = 0; i < m; i++)
        if (agg + a[i] > x) agg = a[i], cnt += 1;
        else agg += a[i];
    return cnt <= k;
}

void print(long long x)
{
    long long agg = 0;
    memset(divider, 0, sizeof(divider));
    int remain = k-1; // unassigned dividers #
    for (int i = m-1; i >= 0; i--)
        if (agg + a[i] > x || i < remain)
            divider[i] = true, remain--, agg = a[i]; 
        else agg += a[i];
    for (int i = 0; i < m-1; i++)
    {
        cout << a[i] << " ";
        if (divider[i]) cout << "/ ";
    }
    cout << a[m-1] << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> m >> k;
        LL sum = 0;
        int mx = -1;
        for (int i = 0; i < m; i++)
        {
            cin >> a[i];
            sum += a[i];
            mx = max(mx, a[i]);
        }
        long long L = max((LL)mx, sum / m + 1), R = sum;
        while (L < R)
        {
            long long M = L + (R-L) / 2;
            if (solve(M)) R = M;
            else L = M + 1;
        }
        print(L);
    }
    return 0;
}
