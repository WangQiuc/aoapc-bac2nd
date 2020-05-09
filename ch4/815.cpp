// UVa509 RAID
// wangqc

#include <stdio.h>
#include <string.h>

int d, s, b, mask;
char disk[7][6500];

int check()
{
    for (int j = 0; j < b*s; j++)
    {
        int bad = -1, par = mask;
        for (int i = 0; i < d; i++)
        {
            if (disk[i][j] == 'x')
            {
                if (bad == -1) bad = i;
                else return 0;
            }
            else par ^= (disk[i][j] - '0');
        }
        if (bad != -1) disk[bad][j] = par + '0';
        else if (par) return 0;
    }
    return 1;
}

int main()
{
    int kase = 0;
    char c;
    while (scanf("%d", &d) && d) 
    {  
        memset(disk, 0, sizeof(disk));
        scanf("%d%d\n%c", &s, &b, &c);
        mask =  c == 'O';
        for (int i = 0; i < d; i++)
            scanf("%s", disk[i]);
        
        if (check()) 
        {
            printf("Disk set %d is valid, contents are: ", ++kase);
            int hex = 0, cnt = 0;
            for (int j = 0; j < b; j++)
                for (int i = 0; i < d; i++)
                {
                    if (i == j % d) continue;   // parity block
                    for (int k = 0; k < s; k++)
                    {
                        hex = hex << 1 | disk[i][j*s+k] - '0';
                        if (++cnt == 4)
                            printf("%X", hex), hex = cnt = 0;
                    }

                }
            if (cnt) printf("%X", hex << (4-cnt));
            printf("\n");
        }
        else printf("Disk set %d is invalid.\n", ++kase);
    }
    return 0;
}
