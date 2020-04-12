// wangqc

#include <stdio.h>

int check(int x)
{
    int bitmap = 0;
    for (int y = x; y <= 3 * x; y += x)
    {
        for (int d = 1; d <= 100; d *= 10)
        {
            int i = y / d % 10;
            if (!i || bitmap & (1 << i)) return 0;
            bitmap |= 1 << i;
        }
    }
    return 1;
}

int main()
{   
    const int LO = 123, HI = 327;  // HI * 3 = 981; 987 and 984 are not valid
    for (int x = LO; x <= HI; x++) 
        if (check(x)) 
            printf("%d\n", x * 1000000 + x * 2000 + x * 3);
    return 0;
}