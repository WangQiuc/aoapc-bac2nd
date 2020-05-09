// UVa1572 Self-Assembly
// wangqc

#include<iostream>
#include<cstring>

using namespace std;

int ID(char symbol, char sign) { return ((symbol - 'A') << 1) + (sign == '+'); }
int graph[52][52];
int c[52];

// if mocular has edges a+, b-, then it can connects with edge a-, b+
void connect(char x1, char x2, char y1, char y2)
{
    if (x1 == '0' || y1 == '0') return;
    graph[ID(x1, x2)][ID(y1, y2) ^ 1] = 1;
    graph[ID(y1, y2)][ID(x1, x2) ^ 1] = 1;
}

bool dfs(int x)
{
    c[x] = -1;
    for (int y = 0; y < 52; y++)
        if (graph[x][y] && (c[y] < 0 || (!c[y] && dfs(y))))
            return true;
    c[x] = 1;
    return false;
}

bool has_cycle()
{
    memset (c, 0, sizeof(c));
    for (int x = 0; x < 52; x++)
        if (!c[x] && dfs(x)) return true;
    return false;
}

int main()
{
    int n;
    while (cin >> n && n)
    {
        memset(graph, 0, sizeof(graph));
        while (n--)
        {
            string s;
            cin >> s;
            for (int i = 0; i < 3; i++)
                for (int j = i + 1; j < 4; j++)
                    connect(s[i<<1], s[(i<<1)+1], s[j<<1], s[(j<<1)+1]);
        }
        cout << (has_cycle() ? "unbounded" : "bounded") << endl;
    }
    return 0;
}
