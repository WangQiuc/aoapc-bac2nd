// UVa699 The Falling Leaves
// wangqc

#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 200;
int sum[maxn];

void dfs(int p)
{
    int v; cin >> v;
    if (v == -1) return;
    sum[p] += v;
    dfs(p-1); dfs(p+1);
}

bool init()
{
    int v; cin >> v;
    if (v == -1) return false;
    memset(sum, 0, sizeof(sum));
    int p = maxn >> 1;
    sum[p] = v;
    dfs(p-1); dfs(p+1);
    return true;
}

int main()
{
    int kase = 0;
    while(init())
    {
        int p = 0;
        while(!sum[p]) p++;
        cout << "Case " << ++kase << ":\n" << sum[p++];
        while(sum[p]) cout << " " << sum[p++];
        cout << "\n\n";
    }
    return 0;
}
