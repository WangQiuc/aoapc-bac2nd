// UVa 140
// wangqc
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 10;
int id[26], nodes[maxn];

int main()
{
    char input[100];
    while (scanf("%s", input) == 1 && input[0] != '#')
    {
        int n = 0;
        for (char c = 'A'; c <= 'Z'; c++)
            if (strchr(input, c) != NULL)
            {
                nodes[n] = c;
                id[c - 'A'] = n++;
            }
        int len = strlen(input), p = 0, q = 0;
        vector<int> u, v;
        for(;;)
        {
            while (p < len && input[p] != ':') p++;
            if (p == len) break;
            while (q < len && input[q] != ';') q++;
            for (int i = p+1; i < q; i++)
            {
                u.push_back(id[input[p-1] - 'A']);
                v.push_back(id[input[i] - 'A']);
            }
            p++, q++;
        }
        int P[maxn], bestP[maxn], pos[maxn], best = n;
        for (int i = 0; i < n; i++) P[i] = i;
        do
        {
            for (int i = 0; i < n; i++) pos[P[i]] = i;
            int bandwidth = 0;
            for (int i = 0; i < u.size(); i++)
            {
                bandwidth = max(bandwidth, abs(pos[u[i]] - pos[v[i]]));
                if (bandwidth >= best) break;       // prune
            }
            if (bandwidth < best)
            {
                best = bandwidth;
                memcpy(bestP, P, sizeof(P));
            }
        } while (next_permutation(P, P+n));
        for (int i = 0; i < n; i++) printf("%c ", nodes[bestP[i]]);
        printf("-> %d\n", best);
    }
    return 0;
}
