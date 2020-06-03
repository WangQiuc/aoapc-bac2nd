// UVa 1621 Jumping Around
// wangqc
#include<cstdio>

using namespace std;

int main()
{
    int a, b, c, T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &a, &b, &c);
        int p = 0;
        printf("0");
        if (c % 3 == 0)
        {
            for (int i = 0; i < c / 3; i++) printf(" %d", p += 3);
            printf(" %d", ++p);
            for (int i = 0; i < c / 3; i++) printf(" %d", p -= 3);
            printf(" %d", ++p);
            for (int i = 0; i < c / 3; i++) printf(" %d", p += 3);
            a -= 2;
        }
        else if (c % 3 == 1)
        {
            for (int i = 0; i <= c / 3; i++) printf(" %d", p += 3);
            printf(" %d", p -= 2);
            for (int i = 0; i < c / 3; i++) printf(" %d", p -= 3);
            printf(" %d", ++p);
            for (int i = 0; i < c / 3; i++) printf(" %d", p += 3);
            printf(" %d", p += 2);
            a -= 1, b -= 2;
        }
        else
        {
            for (int i = 0; i <= c / 3; i++) printf(" %d", p += 3);
            printf(" %d", --p);
            for (int i = 0; i < c / 3; i++) printf(" %d", p -= 3);
            printf(" %d", ++p);
            for (int i = 0; i <= c / 3; i++) printf(" %d", p += 3);
            a -= 2;
        }
        for (int i = 0; i < a-1; i++) printf(" %d", ++p);
        for (int i = 0; i < (b+1)>>1; i++) printf(" %d", p += 2);
        printf(" %d", b & 1 ? --p : ++p);
        for (int i = b & 1; i < (b+1)>>1; i++) printf(" %d", p -= 2);
        printf("\n");
    }
    return 0;
}
