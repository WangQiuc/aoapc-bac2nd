// UVa455 Periodic Strings
// wangqc

#include <stdio.h>

int main()
{
    int x, y, valid, kase = 0;
    char c, s[5][7];

    while ((c = getchar()) != 'Z')
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j <= 5; j++)
            {
                if ((s[i][j] = c) == ' ')
                    x = i, y = j;
                if (i + j != 9)
                    c = getchar();
            }
        }
        valid = 1;
        while ((c = getchar()) != '0')
        {
            if (!valid) continue;
            if (c == 'A')
            {
                if (x == 0) valid = 0;
                else s[x--][y] = s[x-1][y];
            }
            if (c == 'B')
            {
                if (x == 4) valid = 0;
                else s[x++][y] = s[x+1][y];
            }
            if (c == 'L')
            {
                if (y == 0) valid = 0;
                else s[x][y--] = s[x][y-1];
            }
            if (c == 'R')
            {
                if (y == 4) valid = 0;
                else s[x][y++] = s[x][y+1];
            }
            s[x][y] = ' ';
        }
        getchar(); // handle '\n'
        if (kase) printf("\n");
        printf("Puzzle #%d:\n", ++kase);
        if (valid)
        {
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    printf("%c%c", s[i][j], j == 4 ? '\n' : ' ');
        }
        else
            printf("This puzzle has no final configuration.\n");
    }
    return 0;
}