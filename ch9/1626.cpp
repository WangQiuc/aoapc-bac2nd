// UVa 1626 Brackets sequence
// wangqc
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 105;
char s[maxn];
int n, memo[maxn][maxn];

bool match(char a, char b)
{
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

void dfs()
{
    for (int i = 0; i < n; i++)
        memo[i+1][i] = 0, memo[i][i] = 1;       // need a bracket to match s[i]
    for (int i = n-2; i >= 0; i--)
        for (int j = i+1; j < n; j++)
        {
            memo[i][j] = n;
            if (match(s[i], s[j])) memo[i][j] = memo[i+1][j-1];
            for (int k = i; k < j; k++)
                memo[i][j] = min(memo[i][j], memo[i][k]+memo[k+1][j]);
        }
}

void print(int i ,int j)
{
    if (i == j)
        printf(s[i] == '(' || s[i] == ')' ? "()" : "[]");
    else if (i < j)
    {
        int cnt = memo[i][j];
        if (match(s[i], s[j]) && cnt == memo[i+1][j-1])
            printf("%c", s[i]), print(i+1, j-1), printf("%c", s[j]);
        else for (int k = i; k < j; k++) if (cnt == memo[i][k]+memo[k+1][j])
        {   print(i, k), print(k+1, j); break;  } 
    }
}

int main()
{
    int T;
    fgets(s, maxn, stdin);
    sscanf(s, "%d", &T);
    fgets(s, maxn, stdin);
    while (T--)
    {
        fgets(s, maxn, stdin);  // need to handle empty string
        n = strlen(s)-1;
        memset(memo, 0, sizeof(memo));
        dfs();
        print(0, n-1);
        printf(T ? "\n\n" : "\n");
        fgets(s, maxn, stdin);  // read blank line
    }
    return 0;
}
