// UVa 1633 Dyslexic Gollum
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int M = 1000000007;

int dp[405][1<<11];
int pal[13][1<<11];  // pal[k][s], s's k-length bit string is palidrome

inline int get_bit(int x, int i) { return x >> i & 1; }

inline bool is_pal(int k, int s)
{
    for (int i = 0; i < k>>1; i++)
        if (get_bit(s, i) != get_bit(s, k-1-i)) return false;
    return true;

}

void init()  // precompute all palidrome
{
    for (int k = 1; k <= 11; k++)
        for (int s = 0; s < 1<<k; s++)
            pal[k][s] = is_pal(k, s);
}

int main()
{
    init();
    int n, k, T;
    cin >> T;
    while(T--)
    {
        cin >> n >> k;
        if (k == 1) { cout << 0 << endl; continue; }
        memset(dp, 0, sizeof(dp));
        int ans = 0, kmask = (1<<k)-1;
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int s0 = 0; s0 < 1<<min(i,k); s0++) if (dp[i-1][s0])
            {   // s0: current last k bit string, s/sk: next last k+1/k bit string
                for (int s = s0<<1; s <= (s0<<1|1); s++)
                {
                    int sk = s & kmask;
                    if ((i >= k && pal[k][sk]) || (i > k && pal[k+1][s])) continue;  
                    dp[i][sk] = (dp[i][sk] + dp[i-1][s0]) % M;
                }
            }
        for (int s = 0; s < 1 << k; s++)
            ans = (ans + dp[n][s]) % M;
        cout << ans << endl;
    }
    return 0;
}
