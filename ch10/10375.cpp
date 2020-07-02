// UVa 10375 Choose and divide
// wangqc
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>

using namespace std;

const int maxn = 10000;
vector<int> primes;
int e[maxn];

bool is_prime(int x)
{
    int n = floor(sqrt(x) + 0.5);
    for(int i = 2; i <= n; i++)
        if(!(x % i)) return false;
    return true;
}

//  add prime factor of n with d
void add_factorial(int n, int d)
{
    for(int x = 1; x <= n; x++)
        for(int i = 0; i < primes.size(); i++)
        {
            int t = x;
            while(t % primes[i] == 0)
                t /= primes[i], e[i] += d;
            if(t == 1) break; 
        }
}

int main()
{
    for(int i = 2; i <= maxn; i++)
        if(is_prime(i)) primes.push_back(i);
    int p, q, r, s;
    while(cin >> p >> q >> r >> s)
    {   // (p!*(q!*(p-q)!)) / (r!*(s!*(r-s)!))
        memset(e, 0, sizeof(e));
        add_factorial(p, 1);
        add_factorial(q, -1);
        add_factorial(p-q, -1);
        add_factorial(r, -1);
        add_factorial(s, 1);
        add_factorial(r-s, 1);
        double ans = 1;
        for(int i = 0; i < primes.size(); i++)
            ans *= pow(primes[i], e[i]);
        printf("%.5lf\n", ans);
    }
    return 0;
}
