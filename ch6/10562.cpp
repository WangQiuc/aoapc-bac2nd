// UVa10562 Undraw the Trees
// wangqc

#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

const int maxn = 205;
int n;
char buf[maxn][maxn];

bool vacant(char c) { return isspace(c) || c == '#'; }

void dfs(int r, int c)
{
    printf("%c(", buf[r][c]);
    if (r < n-1 && buf[r+1][c] == '|')
    {
        int i = c;
        while (i-1 >= 0 && buf[r+2][i-1] == '-') i--;
        while (buf[r+2][i] == '-' && buf[r+3][i] != '\0')
        {
            if (!vacant(buf[r+3][i])) dfs(r+3, i);
            i++;
        }
    }
    printf(")");
}

int main()
{
    int T;
    scanf("%d\n", &T);
    while(T--)
    {
        n = 0;
        while(fgets(buf[n], maxn, stdin) && buf[n][0] != '#') n++;
        printf("(");
        if (n)
        {
            int i = 0;
            while(vacant(buf[0][i])) i++;
            dfs(0, i);
        }
        printf(")\n");
    };
    return 0;
}
