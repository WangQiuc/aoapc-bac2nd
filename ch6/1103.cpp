// UVa1103 Ancient Messages
// wangqc

#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const char *code = "WAKJSD";
const char bin[16][5] = 
{
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111",
};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int maxn = 205;
char line[maxn];
int m, n, pic[maxn][maxn], color[maxn][maxn];
vector<set<int> > neighbors;

void decode(char c, int x, int y)
{
    int id = c - (isalpha(c) ? 'a' - 10 : '0');
    for (int i = 0; i < 4; i++)
        pic[x][y+i] = bin[id][i] - '0'; 
}

void dfs(int x, int y, int c)
{
    color[x][y] = c;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && pic[x][y] == pic[nx][ny] && !color[nx][ny])
            dfs(nx, ny, c);
    }
}

void eval(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !pic[nx][ny] && color[nx][ny] != 1)
            neighbors[color[x][y]].insert(color[nx][ny]);
    }
}

int main()
{
    int cnt, kase = 0;
    while (scanf("%d%d", &m, &n) == 2 && m && n)
    {
        memset(pic, 0, sizeof(pic));
        for (int i = 1; i <= m; i++)
        {
            scanf("%s", line);
            for (int j = 0; j < n; j++)
                decode(line[j], i, j*4+1);
        }
        m += 2, n = n*4 + 2, cnt = 0;
        vector<int> cc;
        memset(color, 0, sizeof(color));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!color[i][j])
                {
                    dfs(i, j, ++cnt);
                    if (pic[i][j]) cc.push_back(cnt);
                }         
        neighbors.clear();
        neighbors.resize(cnt + 1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pic[i][j]) eval(i, j);
        vector<char> msg;
        for (int i : cc)
            msg.push_back(code[neighbors[i].size()]);
        sort(msg.begin(), msg.end());
        printf("Case %d: ", ++kase);
        for (char c : msg) 
            printf("%c", c);
        printf("\n");
    }
    return 0;
}
