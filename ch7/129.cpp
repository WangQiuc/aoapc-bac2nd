// UVa 129 Krypton Factor
// wangqc
#include<cstdio>

int n, L, cnt;
int S[100];

bool dfs(int cur)
{
    if (cnt++ == n)     // output nth hard sequence
    {
        for (int i = 0; i < cur; i++)
        {
            if (i && !(i % 64)) printf("\n");
            else if (i && !(i % 4)) printf(" ");
            printf("%c", S[i] + 'A');
        }
        printf("\n%d\n", cur);
        return true;
    }
    for (int i = 0; i < L; i++)
    {
        S[cur] = i;
        bool ok = true;
        for (int len = 1; ok && len * 2 <= cur + 1; len++)
        {
            bool eq = true;
            for (int j = 0; eq && j < len; j++)
                eq = S[cur-j] == S[cur-len-j];
            ok = !eq;
        }
        if (ok && dfs(cur + 1)) return true;
    }
    return false;
}

int main()
{
    while (scanf("%d%d", &n, &L) == 2 && n)
    {
        cnt = 0;
        dfs(0);
    }
    return 0;
}
