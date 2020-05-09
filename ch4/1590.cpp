// UVa1590 IP Networks
// wangqc

#include <stdio.h>

int prefix(int bits)
{
    int i = 0;
    while (bits) bits >>= 1, i++;
    return i;
}

int netmask(int masklen)  // handle -1 << 32, should be 0 instead of -1
{
    return masklen == 32 ? 0 : -1 << masklen;
}

void printip(int ip)
{
    printf("%d.%d.%d.%d\n", 
        ip >> 24 & 0xFF, ip >> 16 & 0xFF, ip >> 8 & 0xFF, ip & 0xFF);
}

int main()
{
    int T;
    while(scanf("%d", &T) == 1)
    {
        int s1, s2, s3, s4, host, subnet, masklen = 0, first = 1;
        while (T--)
        {
            scanf("%d.%d.%d.%d", &s1, &s2, &s3, &s4);
            if (masklen == 32) continue;  // max subnet, no need to proceed
            host = s1 << 24 | s2 << 16 | s3 << 8 | s4;
            if (first) 
                subnet = host, first = 0;
            else
            {
                if ((subnet ^ host) >> 31) masklen = 32;
                else masklen += prefix((subnet ^ host) >> masklen);
                subnet &= netmask(masklen);
            }
        }
        printip(subnet);
        printip(netmask(masklen));
    }
    return 0;
}
