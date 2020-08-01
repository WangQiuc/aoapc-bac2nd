// UVa 1664 Conquer a New Region
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 200005, inf = 0x3f3f3f3f;
typedef long long ll;

struct Edge
{
    int x, y;
    ll w;
    bool operator < (const Edge &rhs) const { return w > rhs.w; }
} edges[maxn];

int p[maxn];
ll cnt[maxn], sum[maxn];

int find(int x) { return x == p[x] ? x : p[x]=find(p[x]); }

int main()
{
    int n;
    while(cin >> n)
    {
        for(int i = 1; i < n; i++)
            cin >> edges[i].x >> edges[i].y >> edges[i].w;
        sort(edges+1, edges+n);
        for(int i = 1; i <= n; i++) 
            p[i] = i, sum[i] = 0, cnt[i] = 1;
        for(int i = 1; i < n; i++)
        {
            int x = find(edges[i].x);
            int y = find(edges[i].y);
            ll sx = sum[x] + cnt[y]*edges[i].w;
            ll sy = sum[y] + cnt[x]*edges[i].w;
            if(sx < sy) 
            {   switch(x, y); sx = sy; }
            p[y] = x;
            cnt[x] += cnt[y];
            sum[x] = sx;
        }
        cout << sum[find(edges[n-1].x)] << endl;
    }
    return 0;
}
