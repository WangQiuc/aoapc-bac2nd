// UVa1585 Score
// wangqc

#include <stdio.h>
#include <string.h>
#define maxn 85

int main()
{
    int cnt, tot, T;
    char s[maxn];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = strlen(s), cnt = 0, tot = 0;
        for (int i = 0; i < n; i++)
        {
            cnt = s[i] == 'O' ? cnt + 1 : 0;
            tot += cnt;
        }
        printf("%d\n", tot);
    }
    return 0;
}