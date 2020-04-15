// UVa10340 All in All
// wangqc

#include <stdio.h>
#include <string.h>

#define maxn 100005

int main()
{
    char s[maxn], t[maxn];
    while ((scanf("%s %s", s, t)) == 2)
    {
        int i = 0, j = 0, m = strlen(s) - 1, n = strlen(t);
        for (; i <= m; i++)
        {
            while (j < n && s[i] != t[j++]);
            if (j == n) break;
        }
        printf((i >= m && s[m] == t[j - 1]) ? "Yes\n" : "No\n");
    }
    return 0;
}