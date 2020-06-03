// UVa 1620 Lazy Susan
// wangqc
#include<iostream>

using namespace std;

const int maxn = 505;
int n, a[maxn];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        int cnt = 0;
        for (int i = 0; i < n-1; i++)
            for (int j = i+1; j<n; j++)
                cnt += a[i] > a[j];
        cout << (n & 1 && cnt & 1 ? "impossible" : "possible") << endl;
    }
    return 0;
}
