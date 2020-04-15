// UVa1586 Molar Mass
// wangqc

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define maxn 85


double mass(char c)
{
    if (c == 'C') return 12.01;
    if (c == 'H') return 1.008;
    if (c == 'O') return 16.00;
    if (c == 'N') return 14.01;
    return 0.0;
}


int main()
{
    int cnt, tot, T;
    char s[maxn];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = 0, len = strlen(s);
        double x = 0, tot = 0;
        for (int i = 0; i < len; i++)
        {
            if (isalpha(s[i])) 
            {
                tot += x * (n ? n : 1);
                x = mass(s[i]);
                n = 0;
            } 
            else n = n * 10 + s[i] - '0';
        }
        printf("%.3f\n", tot + x * (n ? n : 1));
    }
    return 0;
}