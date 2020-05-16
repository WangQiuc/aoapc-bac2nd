// UVa 690 Pipeline Scheduling
// wangqc
#include<cstdio>

int n, m, mint, p[5], w[20];
char buf[25];

bool compatible(int *q, int k)   // new job p compatible with (q after t time)
{
    for (int i = 0; i < 5; i++)
        if (q[i] >> k & p[i]) return false;
    return true;
}

void dfs(int *q, int d, int t)   // dth job, costed t time
{
    if (t + w[0]*(10-d) >= mint) return;
    for (int k = 0; k < m; k++)
        if (compatible(q, w[k]))
        {
            int nq[5];
            for (int i = 0; i < 5; i++) 
                nq[i] = q[i]>>w[k] | p[i];
            if (d < 9) dfs(nq, d+1, t+w[k]);
            else if (t+w[k] < mint) mint = t+w[k];    // base case d == 9
        }
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < 5; i++)
        {
            p[i] = 0;
            scanf("%s", buf);
            for (int j = 0; j < n; j++)
                if (buf[j] == 'X') p[i] |= 1 << j;
        }
        mint = 10 * n, m = 0;
        for (int k = 1; k <= n; k++)
            if (compatible(p, k)) w[m++] = k;
        dfs(p, 1, n);
        printf("%d\n", mint);  
    }
    return 0;
}
