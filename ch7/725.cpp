// UVa 11059 Maximum Product
// wangqc
#include<cstdio>
#include<cstring>

using namespace std;

bool valid(char *buf)
{
    bool slot[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        if (slot[buf[i] - '0']) return false;
        slot[buf[i] - '0'] = true;
    }
    return true;
}

int main()
{
    int x;
    bool first = false;
    char buf[15];
    while (scanf("%d", &x) && x)
    {
        if (first) printf("\n");
        else first = true;
        int cnt = 0;
        for (int y = 1234; ; y++)
        {
            int z = x * y;
            sprintf(buf, "%05d%05d", z, y);
            if (strlen(buf) > 10) break;
            if (valid(buf))
            {
                printf("%05d / %05d = %d\n", z, y, x);
                cnt++;
            }
        }
        if (!cnt) printf("There are no solutions for %d.\n", x);
    }
    return 0;
}
