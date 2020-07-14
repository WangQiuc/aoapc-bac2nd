// UVa 1390 Interconnect
// wangqc
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
const int maxn = 30, M = 100007;
int n, m, P[maxn+5], sz[maxn+5];
double base;

struct status
{
    int x[maxn];
    bool used;
    double exp;     // status's expectation
    int hash()
    {
        int h = 0;
        for(int i = 0; i < maxn; i++)
            h = (h*maxn + x[i]) % M;
        return h;
    }
    bool operator == (const status &rhs)
    {
        for(int i = 0; i < 30; i++)
            if(x[i] != rhs.x[i]) return false;
        return true;
    }
    bool operator != (const status &rhs) { return !(*this == rhs); }
} st, H[M+7];

int find(int x) { return x == P[x] ? x : (P[x] = find(P[x])); }

void unite(int x, int y)
{
    int px = find(x), py = find(y);
    if(px == py) return;
    if(sz[px] < sz[py]) swap(px, py);
    P[py] = px, sz[px] += sz[py];
}

// linear probing hash
double get_exp(status s)
{
    int h = s.hash();
    while(H[h].used && H[h] != s )
        if(++h == M) h = 0;
    return H[h] == s ? H[h].exp : -1;
}

void insert(status s)
{
    int h = s.hash();
    while(H[h].used)
        if(++h == M) h = 0;
    s.used = true;
    H[h] = s;
}

double dp(status s)
{
    sort(s.x, s.x+maxn);
    if(s.hash() == n) return 0;
    double e = get_exp(s);
    if (e != -1.0) return e;
    double p = 0, ans = 0;
    for(int i = 0; i < maxn; i++)
        p += s.x[i]*(s.x[i]-1) / 2.0;
    for(int i = 0; i < maxn; i++)
    {
        if(!s.x[i]) continue;
        for(int j = i+1; j < maxn; j++)
        {
            if(!s.x[j]) continue;
            status t = s;
            t.x[i] += t.x[j], t.x[j] = 0;
            ans += s.x[i]*s.x[j]*dp(t);
        }
    }

    s.exp = (ans/base + 1) / (1 - p/base);
    insert(s);
    return s.exp;
}

int main()
{
    int x, y;
    while(scanf("%d%d", &n, &m) == 2)
    {
        memset(st.x, 0, sizeof(st.x));
        base = n * (n-1) / 2.0;
        for(int i = 0; i < M; i++) H[i].used = false;
        for(int i = 1; i <= n; i++) P[i] = i, sz[i] = 1;
        while(m--)
        {
            scanf("%d%d", &x, &y);
            unite(x, y);
        }
        for(int i = 1; i <= n; i++) if(i == P[i]) st.x[i-1] = sz[i];
        printf("%.6lf\n", dp(st));
    }
    return 0;
}
