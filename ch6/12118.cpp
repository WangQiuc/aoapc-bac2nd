// UVa12188 Inspector's Dilemma (eulerian circuit)
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 1002;
int V, E, w, p[maxn], deg[maxn], ctr[maxn];

int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x;  }

int main()
{
    int kase = 0;
    while (cin >> V >> E >> w && V)
    {
        memset(deg, 0, sizeof(deg));
        memset(ctr, 0, sizeof(ctr));
        for (int i = 1; i <= V; i++) 
            p[i] = i;
        int a, b;
        for (int i = 0; i < E; i++)
        {
            cin >> a >> b; 
            deg[a]++, deg[b]++;
            int pa = find(a), pb = find(b);
            if (pa != pb) p[pa] = pb;
        }
        vector<int> roots;
        for (int i = 1; i <= V; i++)
        {
            if (deg[i] & 1) ctr[find(i)]++;              // # degrees is odd
            if (deg[i] && p[i] == i) roots.push_back(i); // root of a cc, need an edge to connect
        }

        int cnt = roots.empty() ? 0 : roots.size() - 1;
        for (int root : roots)
            cnt += (ctr[root] - 1) / 2;
        cout << "Case " << ++kase << ": " << (E + cnt) * w << endl;
    }
    return 0;
}
