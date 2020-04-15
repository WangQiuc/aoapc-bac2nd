// UVa1587 Box
// wangqc

#include <stdio.h>
#include <string.h>

int order_scan(int *a, int *b)
{
    int ret = scanf("%d %d", a, b);
    if (*a < *b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }
    return ret;
}

void order_swap(int *a, int *b)
{
    if (a[0] < b[0] || a[1] < b[1])
    {
        int t0 = a[0], t1 = a[1];
        a[0] = b[0], a[1] = b[1];
        b[0] = t0, b[1] = t1;
    }
}

int main()
{
    int box[3][3], x, y, i, ok;
    while (order_scan(&x, &y) == 2)
    {
        memset(box, 0, sizeof(box));
        box[0][0] = x, box[0][1] = y, ok = 1;
        for (int t = 0; t < 5; t++)
        {
            order_scan(&x, &y);
            for (i = 0; i < 3 && ok; i++)
            {
                if (box[i][0] && (x != box[i][0] || y != box[i][1] || box[i][2])) continue;
                if (!box[i][0]) box[i][0] = x, box[i][1] = y;
                else box[i][2] = 1;
                break;
            }
            if (i == 3) ok = 0;
        }
        if (ok)
        {
            order_swap(box[0], box[1]);
            order_swap(box[0], box[2]);
            order_swap(box[1], box[2]);
            ok = box[0][0] == box[1][0] && box[0][1] == box[2][0] && box[1][1] == box[2][1];
        }
        printf(ok ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    }
    return 0;
}