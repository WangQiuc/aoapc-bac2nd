// UVa536 Tree Recovery
// wangqc

#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

char pre[30], in[30];   // 26 characters

void build(int L, int R, int rid)
{
    if (L >= R) return;
    int p = find(in + L, in + R, pre[rid]) - in;
    build(L, p, rid + 1);
    build(p + 1, R, rid + p - L + 1);
    putchar(pre[rid]);
}

int main()
{
    while (scanf("%s%s", pre, in) == 2)
    {
        build(0, strlen(pre), 0);
        putchar('\n');
    }
    return 0;
}
