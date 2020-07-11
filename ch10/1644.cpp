// UVa 1644 Prime Gap
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

const int maxp = 100005, maxn = 1300000;
int p[maxp], ans[maxn];
bool vis[maxn];

void init()  // generate prime table and precompute all prime gap
{
    int n = 0;
    int m = sqrt(maxn + 0.5);
    for(int i = 2; i < maxn; i++) if(!vis[i])
    {
        p[++n] = i;
        if(i <= m) for(int j = i*i; j < maxn; j+=i) vis[j] = true;
    }
    for(int i = 1; i <= n; i++)
        for(int j = p[i-1]+1; j < p[i]; j++) ans[j] = p[i]-p[i-1];
}

int main()
{
    init();
    int n;
    while(cin >> n && n)
        cout << ans[n] << endl;
    return 0;
}
