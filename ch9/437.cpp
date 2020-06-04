// UVa
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 35;
int n, block[maxn][3], memo[maxn][3];

// get 2 dimensions other than `dim` of block i
void get_dimension(int *v, int i, int dim)  
{
    int p = 0;
    for (int d = 0; d < 3; d++) if (d != dim)
        v[p++] = block[i][d];
}

int dp(int i, int d)   // block i with dimension d as height
{
    int &ans = memo[i][d];
    if (ans > 0) return ans;
    int v[2], v2[2];
    get_dimension(v, i, d);
    for (int j = 0; j < n; j++)
        for (int t = 0; t < 3; t++)
        {
            get_dimension(v2, j, t);
            if (v2[0] < v[0] && v2[1] < v[1])
                ans = max(ans, dp(j, t));
        }
    return ans += block[i][d];
}

int main()
{
    int kase = 0;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int d = 0; d < 3; d++)
                cin >> block[i][d];
            sort(block[i], block[i]+3);
        }

        memset(memo, 0, sizeof(memo));
        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int d = 0; d < 3; d++)
                ans = max(ans, dp(i, d));
        cout << "Case " << ++kase << ": maximum height = " << ans << endl;
    }
    return 0;
}
