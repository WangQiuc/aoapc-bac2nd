// UVa133 The Dole Queue
// wangqc

#include <stdio.h>

int n, k, m, a[22];

int go(int p, int d, int t)
{
    while (t--)
        do {p = (p+d+n-1) % n + 1;} while (!a[p]);
    return p;        
}

int main()
{
    while (scanf("%d%d%d", &n, &k, &m) == 3 && n)
    {
        for (int i = 1; i <= n; i++) a[i] = i;
        int p1 = n, p2 = 1, left = n;
        while (left)
        {
            p1 = go(p1, 1, k);
            p2 = go(p2, -1, m);
            printf("%3d", p1);
            if (p1 != p2) printf("%3d", p2);
            a[p1] = a[p2] = 0;
            left -= 1 + (p1 != p2);
            if(left) printf(",");
        }
        printf("\n");
    }
    return 0;
}
