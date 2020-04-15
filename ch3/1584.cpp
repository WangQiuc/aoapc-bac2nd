// UVa1584 Cicular Sequence
// wangqc

#include <stdio.h>
#include <string.h>
#define maxn 105

int less(const char *s, int p, int q)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        if (s[(p + i) % n] != s[(q + i) % n])
            return s[(p + i) % n] < s[(q + i) % n] ? p : q;
    return q;
}

int main()
{
    int T;
    char s[maxn];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int p = 0;
        int n = strlen(s);
        for (int i = 1; i < n; i++)
            p = less(s, i, p);
        for (int i = 0; i < n; i++)
            putchar(s[(p + i) % n]);
        putchar('\n');
    }
    return 0;
}