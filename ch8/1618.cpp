// UVa 1618 Weak Key
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 5005;
int n, a[maxn];
vector<int> L[maxn], R[maxn];

bool valid()
{
    for (int i = 0; i < n; i++)
    {
        L[i].clear(), R[i].clear();
        for (int j = i-1; j >= 0; j--) if (a[i] < a[j]) 
            L[i].push_back(a[j]);
        for (int j = i+1; j < n; j++) if (a[i] > a[j]) 
            R[i].push_back(a[j]);
        sort(L[i].begin(), L[i].end());
        sort(R[i].begin(), R[i].end());
    }
    // p < q < r < s, A[q] < A[s] < A[p] < A[r]
    for (int q = 0; q < n; q++)
        for (int r = q+1; r < n-1; r++) if (a[q] < a[r] && !L[q].empty() && !R[r].empty())
        {
            // largest L[q] element that is smaller than a[r]
            int p = lower_bound(L[q].begin(), L[q].end(), a[r]) - L[q].begin() - 1;
            // smallest R[r] element that is larger than a[q]
            int s = upper_bound(R[r].begin(), R[r].end(), a[q]) - R[r].begin();
            if (p >= 0 && s < R[r].size() && R[r][s] < L[q][p]) return true;
        }
    return false;
    
}

bool solve()
{
    if (valid()) return true;
    reverse(a, a+n);
    return valid();
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        cout << (solve() ? "YES" : "NO") << endl;
    }
    return 0;
}
