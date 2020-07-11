// UVa 1213 Sum of Different Primes
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;

const int maxn = 1125;
typedef long long ll;
ll dp[maxn][maxn];
vector<int> primes;
bool vis[maxn];

void init()
{
    int m = sqrt(maxn+0.5), n = 0;
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        primes.push_back(i);
        if(i <= m) for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    }
    dp[0][0] = 1;
    for(int p : primes)
        for(int i = maxn; i >= p; i--)
            for(int k = 1; k <= 14; k++)
                dp[i][k] += dp[i-p][k-1];
                
}

int main()
{
    init();
    int n, k;
    while(cin >> n >> k && n)
        cout << dp[n][k] << endl;
    return 0;
}
