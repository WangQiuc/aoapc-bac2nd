// UVa213 Message Decoding
// wangqc

#include <stdio.h>
#include <string.h>

int readchar()
{
    int c;
    while ((c = getchar()) == '\n' || c == '\r'); 
    return c;
}

int readint(int c)
{
    int v = 0;
    while (c--) 
        v = (v << 1) | (readchar() - '0');
    return v;
}

int header[8][1<<8];

int readheader()
{
    memset(header, 0, sizeof(header));
    header[1][0] = readchar();
    for (int len = 2; len < 8; len++)
    {
        for (int i = 0; i < (1 << len) - 1; i++)
        {
            int c = getchar();
            if (c == EOF) return 0;
            if (c == '\n' || c == '\r') return 1;
            header[len][i] = c;
        }
    }
    return 1;
}

int main()
{
    while (readheader())
    {
        int len, v;
        while ((len = readint(3)))
            while ((v = readint(len)) != (1 << len) - 1)
                putchar(header[len][v]);
        putchar('\n');
    }
    return 0;
}
