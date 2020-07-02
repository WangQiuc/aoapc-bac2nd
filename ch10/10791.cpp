// UVa 10791 Minimum Sum LCM
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

// remove all prime factor p from n
int decompose(int &n, int p)
{
    int x = 1;
    while(n % p == 0)
        n /= p, x *= p;
    return x;
}

long long solve(int n)
{
    if(n == 1) return 2;
    long long ans = 0;
    int m = floor(sqrt(n)+0.5), cnt = 0;
    for(int p = 2; p < m; p++) if(n % p == 0)
        cnt++, ans += decompose(n, p);
    if(n > 1) cnt += 1, ans += n;   // ans += decompose(n, n)
    return ans + (cnt <= 1);        // e.g. n=8, ans=8+1
}

int main()
{
    int n, kase = 0;
    while(cin >> n && n)
        cout << "Case " << ++kase << ": " << solve(n) << endl;
    return 0;
}
