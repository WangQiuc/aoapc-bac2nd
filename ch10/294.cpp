// UVa 294 Divisors
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

const int maxn = 32000;
int np, primes[maxn];
bool vis[maxn];

void init_primes()
{
    int m = sqrt(maxn+0.5);
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        primes[np++] = i;
        if(i <= m) for(int j = i*i; j < maxn; j += i) vis[j] = true;
    }
}

int count(int x)
{
    if (x == 1) return 1;
    int ans = 1;
    for(int i = 0; i < np && primes[i] <= x; i++) if(x % primes[i] == 0)
    {
        int e = 1, p = primes[i];
        while(x % p == 0)
            x /= p, e++;
        ans *= e;
    }
    return ans == 1 ? 2 : ans;  // ans for big prime will be 1, need to return 2
}

int main()
{
    init_primes();
    int T, L, U;
    cin >> T;
    while(T--)
    {
        cin >> L >> U;
        int ans = L, max_cnt = 1;
        for(int x = L; x <= U; x++)
        {
            int cnt = count(x);
            if (cnt > max_cnt) ans = x, max_cnt = cnt;
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, ans, max_cnt);
    }
    return 0;
}
