// UVa804 Petri Net Simulator
// wangqc

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 105;

struct Node {
    int ip, op, ix[maxn], ox[maxn], in[maxn], out[maxn];
} graph[maxn];

int main()
{
    int n, m, tok[maxn], limit, T = 0;
    while (cin >> n && n)
    {
        memset(graph, 0, sizeof(graph));
        for (int i = 1; i <= n; i++)
            cin >> tok[i];
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            int j;
            while (cin >> j && j)
            {
                if (j < 0) graph[i].in[-j]++;
                else graph[i].out[j]++;
            }
            for (j = 1; j <= n; j ++)
            {
                if (graph[i].in[j]) graph[i].ix[graph[i].ip++] = j;
                if (graph[i].out[j]) graph[i].ox[graph[i].op++] = j;
            }
        }
        cin >> limit;
        int cnt = 0;
        bool found = true;  // found any one alive node
        while (found && cnt < limit)
        {
            Node x;
            for (int i = 1; i <= m; i++)
            {
                x = graph[i], found = true;
                for (int j = 0; found && j < x.ip; j++)
                    found = tok[x.ix[j]] >= x.in[x.ix[j]];
                if (found) 
                { 
                    for (int j = 0; j < x.ip; j++)
                        tok[x.ix[j]] -= x.in[x.ix[j]];
                    for (int j = 0; j < x.op; j++)
                        tok[x.ox[j]] += x.out[x.ox[j]];
                    cnt++; 
                    break; 
                }
            }
        }
        printf("Case %d: ", ++T);
        printf(cnt == limit ? "still live " : "dead ");
        printf("after %d transitions\nPlaces with tokens:", cnt);
        for (int i = 1; i <= n; i++)
            if (tok[i]) printf(" %d (%d)", i, tok[i]);
        printf("\n\n");
    }
    return 0;
}
