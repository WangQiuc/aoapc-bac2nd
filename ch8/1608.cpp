// UVa 1608 Non-boring sequences
// wangqc
#include<iostream>
#include<unordered_map>

using namespace std;

const int maxn = 200005;
int a[maxn], lidx[maxn], ridx[maxn];
unordered_map<int, int> idx;

inline bool unique(int x, int L, int R) { return lidx[x] < L && ridx[x] > R; }

bool check(int L, int R)    // divide and conquer
{
    if (L >= R) return true;
    for (int x = 0; L+x <= R-x; x++)
    {
        if (unique(L+x, L, R)) return check(L, L+x-1) && check(L+x+1, R);
        if (L+x == R-x) break;
        if (unique(R-x, L, R)) return check(L, R-x-1) && check(R-x+1, R);
    }
    return false;
}

int main()
{
    int n, T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        idx.clear();
        for (int i = 0; i < n; i++) 
        {
            cin >> a[i];
            lidx[i] = idx.count(a[i]) ? idx[a[i]] : -1;
            idx[a[i]] = i;
        }
        idx.clear();
        for (int i = n-1; i >= 0; i--) 
        {
            ridx[i] = idx.count(a[i]) ? idx[a[i]] : n;
            idx[a[i]] = i;
        }
        cout << (check(0, n-1) ? "non-boring" : "boring") << endl;
    }
    return 0;
}
