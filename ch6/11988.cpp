// UVa11988 Broken Keyboard
// wangqc

#include <cstdio>
#include <cstring>

const int maxn = 100005;
int last, curr, next[maxn];
char s[maxn];

int main()
{
    while (scanf("%s", s+1) == 1)
    {
        int n = strlen(s+1);
        next[0] = last = curr = 0;
        for (int i = 1; i <= n; i++)
        {
            char c = s[i];
            if (c == '[') curr = 0;
            else if (c == ']') curr = last;
            else
            {
                next[i] = next[curr];
                next[curr] = i;
                if (curr == last) last = i; 
                curr = i;
            }
        }
        for (int i = next[0]; i != 0; i = next[i])
            printf("%c", s[i]);
        printf("\n");
    }
    return 0;
}
