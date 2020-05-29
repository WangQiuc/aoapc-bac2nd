// UVa 1614 Hell on the Markets
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

const int maxn = 100005;
int a[maxn], id[maxn], sign[maxn];

bool cmp(int i, int j) { return a[i] > a[j]; }

using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        long long s = 0;
        for (int i = 0; i < n; i++)
            cin >> a[i], id[i] = i, s += a[i];
        if (s % 2) 
        {   cout << "No" << endl; continue; }
        s /= 2;
        memset(sign, -1, sizeof(sign));
        sort(id, id + n, cmp);
        for (int i = 0; i < n; i++) if (a[id[i]] <= s) 
            sign[id[i]] = 1, s -= a[id[i]];
        cout << "Yes" << endl;
        for (int i = 0; i < n-1; i++) cout << sign[i] << " ";
        cout << sign[n-1] << endl;
    }
    return 0;
}
