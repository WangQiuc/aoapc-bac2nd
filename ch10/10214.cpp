// UVa 10214 Trees in a Wood
// wangqc
#include<cstdio>
#include<cmath>

int phi(int n)
{
    int m = (int)sqrt(n+0.5);
    int ans = n;
    for(int i = 2; i <= m; i++) if(n % i == 0)
    {
        ans = ans / i * (i-1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans = ans / n * (n-1);
    return ans;
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b) && a)
    {   // all (x, y) that gcd(x, y) == 1, use phi(x) to cover y = [1, kx]
        long long K = 0;
        for(int x = 1; x <= a; x++)
        {
            int k = b / x;
            K += phi(x) * k;
            for(int y = k*x+1; y <= b; y++)
                if(gcd(x, y) == 1) K++;
        }
        K = (K+1) << 2; // f our axis and four quadrants
        long long N = (long long)((a<<1)+1)*((b<<1)+1)-1;   // exclude origin
        printf("%.7lf\n", (double)K / N);
    }
    return 0;
}
