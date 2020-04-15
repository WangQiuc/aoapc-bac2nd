// UVa272 Tex Quotes
// wangqc

#include <stdio.h>
#include <string.h>

int main()
{
    int c, q = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '"')
            printf("%s", (q ^= 1) ? "``" : "''");
        else
            printf("%c", c);
    }
    return 0;
}