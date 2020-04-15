// UVa1588 Kickdown
// wangqc

#include <stdio.h>
#include <string.h>
#include <algorithm> 
using namespace std; 

#define maxn 105
#define base ('0' << 1)

int main()
{
    char s1[maxn], s2[maxn];
    while (scanf("%s %s", s1, s2) == 2)
    {
        int n1 = strlen(s1), n2 = strlen(s2);
        int minlen = n1 + n2;
        for (int i = -n2; i <= n1; i++)
        {
            int ok = 1;
            for (int j = 0; ok && j < n2; j++)
                if (i + j >= 0 && i + j < n1)
                    ok &= s1[i + j] + s2[j] <= 3 + base;
            if (ok) minlen = min(minlen, max(n1, i+n2) - min(i, 0));
        }
        printf("%d\n", minlen);
    }
    return 0;
}