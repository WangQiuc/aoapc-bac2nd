// wangqc

#include<cstdio>
#include<cstring>

using namespace std;

typedef int State[9];
const int maxstate = 1000000, H = 1000003;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
State st[maxstate], goal;
int dist[maxstate], head[H], next[maxstate];

void init_lookup() { memset(head, 0, sizeof(head)); }

int hash(State &x)
{
    int v = 0;
    for (int i = 0; i < 9; i++)
        v = v * 10 + x[i];
    return v % H;
}

bool try_insert(int x)
{
    int h = hash(st[x]);
    int u = head[h];
    while (u)
    {
        if (memcmp(st[u], st[x], sizeof(st[x])) == 0) return false;
        u = next[u];
    }
    next[x] = head[h], head[h] = x;
    return true;
}

int bfs()
{
    init_lookup();
    int p = 1, q = 2;
    while (p < q)        // slide from state p to state q
    {
        State &s = st[p];
        if (memcmp(goal, s, sizeof(s)) == 0)
            return dist[p];
        int z0 = 0;      // index of zero
        while (s[z0]) z0++;
        int x0 = z0 / 3, y0 = z0 % 3;
        for (int d = 0; d < 4; d++)
        {
            int x = x0 + dx[d], y = y0 + dy[d];
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                int z = x *3 + y;
                State &t = st[q];
                memcpy(&t, &s, sizeof(s));
                t[z] = 0, t[z0] = s[z];
                dist[q] = dist[p] + 1;
                if (try_insert(q)) q++;
            }
        }
        p++;
    }
    return -1;
}

int main()
{
    for (int i = 0; i < 9; i++) scanf("%d", &st[1][i]);
    for (int i = 0; i < 9; i++) scanf("%d", &goal[i]);
    printf("%d\n", bfs());
    return 0;
}
