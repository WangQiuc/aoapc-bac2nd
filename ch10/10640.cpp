// UVa 10640 Planes around the World
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 200, inf = 10000;
const double eps = 0.0001;
// 1st group fly upper cycle, one of them is the chosen one, upper = a/b which is the single plane's capacity
// 2nd group fly lower cycle, lower = 1-a/b, the rest distance to support that upper chosen one
double upper, lower;

int solve()
{
    int ans = inf;
    double d;  // distance the chosen one has flied in lower cycle
    for(int i = 1; i < maxn; i++) // number of upper planes
    {   // each of (i-1) plane supports 1/(i+1) fuel to the chosen one
        d = upper*(i-1)/(i+1)/lower;    // rescale lower distance to 1, rest follows the rescale
        int j = 1;             // number of lower planes
        while(d+eps < 1 && i+j < (maxn<<1))  // the chosen start lower cycle flight
        {   // Δd each lower plane support = fuel / planes number, lower-d is forward distance of the support plane
            double dd = (upper/lower-(1-d)) / (++j);    // rescale lower to 1
            d += dd;
        }
        if(i+j < (maxn<<1)) ans = min(ans, i+j-1);  // chosen one count is duplicated
    }
    return ans < inf ? ans : -1;
}

int main()
{
    int T, a, b;
    cin >> T;
    for(int kase = 1; kase <= T; kase++)
    {
        cin >> a >> b;
        if(a >= b) { printf("Case %d: 1\n", kase); continue; }
        upper = (double)a / b, lower = 1-upper;
        printf("Case %d: %d\n", kase, solve());
    }
    return 0;
}
