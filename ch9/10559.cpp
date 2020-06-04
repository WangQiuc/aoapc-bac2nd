// UVa 10559 Blocks
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 205;
int n, A[maxn], d[maxn][maxn][maxn];

int dp(int i, int j, int k)
{   // i--**q1--**q2--p****j
    if (i > j) return 0;
    int &ans = d[i][j][k];
    if (ans >= 0) return ans;
    int p = j;
    while (p >= i && A[p] == A[j]) p--;
    p++;    // leftmost the A[i] color cover
    ans = dp(i, p-1, 0) + (j-p+1+k)*(j-p+1+k); // remove [p, j(k)] block
    for (int q = i; q < p; q++)
        if (A[q] == A[j] && A[q] != A[q+1])
            ans = max(ans, dp(q+1, p-1, 0) + dp(i, q, j-p+1+k)); // or handle [q+1, p-1] first
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> A[i];
        memset(d, -1, sizeof(d));
        cout << "Case " << kase << ": " << dp(0, n-1, 0) << endl;
    }
    return 0;
}
