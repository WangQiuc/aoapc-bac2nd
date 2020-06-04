// UVa 1204 Fun Game
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

const int maxn = 16, maxlen = 105;
int n, len[maxn], overlap[maxn][maxn][2][2];
string nodes[maxn][2];   // nodes[i][0] si, nodes[i][1] rev(si)
int d[1<<maxn][maxn][2]; // d[s][i][x] min length if we used string set s and last string is nodes[i][x]
struct Node
{
    string s, rev;
    bool operator < (const Node &rhs) const { return s.length() < rhs.s.length(); }
};

inline void update(int &x, int v) { if (x < 0 || x > v) x = v; }

inline bool not_sub(const string &a, const string &b) { return a.find(b) == string::npos; }

int get_overlap(const string &a, const string &b)
{
    int n1 = a.length(), n2 = b.length();
    for (int i = max(0, n1-n2)+1; i < n1; i++)
    {
        bool ok = true;
        for (int j = 0; ok && i+j < n1; j++)
            ok = a[i+j] == b[j];
        if (ok) return n1 - i;
    }
    return 0;
}

// read and remove strings that are others' substring
void init()
{
    Node buf[maxn];
    for (int i = 0; i < n; i++)
    {
        cin >> buf[i].s;
        buf[i].rev = buf[i].s;
        reverse(buf[i].rev.begin(), buf[i].rev.end());
    }
    int n2 = 0;
    sort(buf, buf+n);
    for (int i = 0; i < n; i++)
    {
        bool ok = true;
        for (int j = i+1; ok && j < n; j++)
            ok = not_sub(buf[j].s, buf[i].s) && not_sub(buf[j].rev, buf[i].s);
        if (ok)
        {
            nodes[n2][0] = buf[i].s, nodes[n2][1] = buf[i].rev;
            len[n2++] = buf[i].s.length();
        }
    }
    n = n2;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int x = 0; x < 2; x++)
                for (int y = 0; y < 2; y++)
                    overlap[i][j][x][y] = get_overlap(nodes[i][x], nodes[j][y]);
}

void dp()
{
    memset(d, -1, sizeof(d));
    d[1][0][0] = len[0];
    int full = (1 << n) - 1;
    for (int s = 1; s < full; s++)
        for (int i = 0; i < n; i++)
            for (int x = 0; x < 2; x++) if (d[s][i][x] >= 0)
                for (int j = 1; j < n; j++) if (!(s & (1<<j)))  // j is not placed
                    for (int y = 0; y < 2; y++)
                        update(d[s|(1<<j)][j][y], d[s][i][x]+len[j]-overlap[i][j][x][y]);
    int ans = -1;
    for (int i = 0; i < n; i++)
        for (int x = 0; x < 2; x++) if (d[full][i][x] >= 0)
            update(ans, d[full][i][x] - overlap[i][0][x][0]);
    cout << max(2, ans) << endl;
}

int main()
{
    while (cin >> n && n)
    {
        init();
        dp();
    }
    return 0;
}
