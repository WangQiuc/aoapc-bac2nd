// UVa11853 Paintball
// wangqc

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn = 1005;
const double len = 1000.0;
double pin, pout, x[maxn], y[maxn], r[maxn];
int n;
bool ok, v[maxn];

bool intersect(int c1, int c2)
{
    return (x[c1]-x[c2])*(x[c1]-x[c2]) + (y[c1]-y[c2])*(y[c1]-y[c2]) <= (r[c1]+r[c2])*(r[c1]+r[c2]);
}

// southmost intersect point between L/R border and a cycle connects to top border
void update_cand(int i)     
{
    if (x[i] <= r[i]) 
        pin = min(pin, y[i] - sqrt(r[i]*r[i] - x[i]*x[i]));
    if (x[i] + r[i] >= len) 
        pout = min(pout, y[i] - sqrt(r[i]*r[i] - (len-x[i])*(len-x[i])));
}

bool dfs(int i)     // check whether top circles connected with bottom circles
{
    v[i] = true;
    if (y[i] <= r[i]) return true;
    for (int j = 0; j < n; j++)
        if (!v[j] && intersect(i, j) && dfs(j))
            return true;
    update_cand(i);
    return false;
}

int main()
{
    while (cin >> n)
    {
        memset(v, 0, sizeof(v));
        ok = true;
        pin = pout = len;
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i] >> r[i];
        for (int i = 0; ok && i < n; i++)
            if ((y[i]+r[i]) >= len && dfs(i)) ok = false;
        if (ok) printf("0.00 %.2lf %.2lf %.2lf\n", pin, len, pout);
        else printf("IMPOSSIBLE\n");
    }
}
