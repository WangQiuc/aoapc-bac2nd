// UVa455 Periodic Strings
// wangqc

#include <stdio.h>
#include <string.h>

#define maxn 85

int main()
{
    int i, k, T;
    char s[maxn];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = strlen(s);
        for (k = 1; k < n; k++)
        {
            if (!(n % k))
            {
                for (i = k; i < n; i++)
                    if (s[i] != s[i % k])
                        break;
                if (i == n)
                    break;
            }
        }
        if (T) printf("%d\n\n", k);
    }
    printf("%d\n", k);
    return 0;
}