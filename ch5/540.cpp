// UVa540 Team Queue
// wangqc

#include <cstdio>
#include <map>
#include <queue>

using namespace std;

const int maxt = 1010;

int main()
{
    int t, kase = 0;
    while (scanf("%d", &t) == 1 && t)
    {
        printf("Scenario #%d\n", ++kase);
        map<int, int> team;
        for (int i = 0; i < t; i++)
        {
            int n, x;
            scanf("%d", &n);
            while(n--) scanf("%d", &x), team[x] = i;
        }
        queue<int> q, subq[maxt];
        char cmd[30];
        while (scanf("%s", cmd) && cmd[0] != 'S')
        {
            if (cmd[0] == 'E')
            {
                int x, t;
                scanf("%d", &x);
                t = team[x];
                if (subq[t].empty()) q.push(t);
                subq[t].push(x);
            }
            else
            {
                int t = q.front();
                printf("%d\n", subq[t].front()); 
                subq[t].pop();
                if (subq[t].empty()) q.pop();
            }
        }
        printf("\n");
    }
    return 0;
}
