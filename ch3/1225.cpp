// UVa1225 Digit Counting
// wangqc

#include <stdio.h>
#include <string.h>

int main()
{
    int n, T, ctr[10];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        memset(ctr, 0, sizeof(ctr));
        for (int i = 1; i <= n; i++)
        {
            int x = i;
            while (x)
            {
                ctr[x % 10]++;
                x /= 10;
            }
        }
        for (int i = 0; i < 9; i++)
            printf("%d ", ctr[i]);
        printf("%d\n", ctr[9]);
    }
    return 0;
}