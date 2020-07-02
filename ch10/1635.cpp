// UVa 1635 Irrelevant Elements
// wangqc
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;

const int maxn = 100005;
bool bad[maxn];

void prime_factor(int n, vector<int> &primes)
{
    int m = floor(sqrt(n)+0.5);
    for(int i = 2; i <= m; i++) if(n % i == 0)
    {
        primes.push_back(i);
        while(n % i == 0) n /= i;
    }
    if(n > 1) primes.push_back(n);
}

// x = p^e* k, given x and p, return e
int decompose(int x, int p)
{
    int e = 0;
    while(x % p == 0)
        x /= p, e++;
    return e;
}

int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        vector<int> primes, ans;
        prime_factor(m, primes);
        memset(bad, 0, sizeof(bad));
        n--;
        for(int p : primes)
        {
            int e = 0, min_e = decompose(m, p);
            // c(n,k) = c(n,k-1) * (n-k+1) / k
            for(int k = 1; k < n; k++)
            {
                e += decompose(n-k+1, p) - decompose(k, p);
                if(e < min_e) bad[k] = true;
            }
        }

        for(int k = 1; k < n; k++)
            if(!bad[k]) ans.push_back(k+1);
        cout << ans.size() << endl;
        if(!ans.empty())
        {
            cout << ans[0];
            for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
        }
        cout << endl;
    }
    return 0;
}
