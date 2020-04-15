// UVa10082 WERTYU
// wangqc

#include <stdio.h>

char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main()
{
    int i, c;
    while ((c = getchar()) != EOF)
    {
        for (i = 1; s[i] && s[i] != c; i++);
        s[i] ? putchar(s[i - 1]) : putchar(c);
    }
    return 0;
}