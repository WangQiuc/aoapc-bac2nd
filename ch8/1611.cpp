// UVa 1611 Crane
// wangqc
#include<iostream>
#include<vector>

using namespace std;

const int maxn = 10005;
int n, cnt, a[maxn], p[maxn];
vector<pair<int, int> > ans;

void exch(int L, int k)     // swap (a[i], a[i+k]) in [L, L+2*k-1]
{
    for (int i = L; i < L+k; i++)
        swap(a[i], a[i+k]);
    ans.push_back(make_pair(L, L+2*k-1));
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ans.clear();
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
        {
            if (a[i] == i) continue;
            int j, k = 0;
            for (j = i; a[j] != i && j <= n; j++)
                k++;
            if (k <= (n-i+1)>>1) exch(i, k);
            else 
            {
                exch(i+((n-i+1)&1), (n-i+1)>>1);
                i--;
            }
        }
        cout << ans.size() << endl;
        for (auto p : ans) cout << p.first << " " << p.second << endl;
    }
    return 0;
}
