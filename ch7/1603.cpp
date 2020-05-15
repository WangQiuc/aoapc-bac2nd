// UVa 1603 Square Destroyer
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxs = 60;    // squares #: 1 + 4 + 9 + 15 + 25 = 55
const int maxm = 60;    // matches #: 2 * 5 * (5 + 1) = 60

int n;
bool slot[maxm];       // has a match on that slot or not
// id of an enumerated square, matches# in square[sid], full number of matches
// in square[sid], edge[sid][mid], whether sqaure[sid] contains matches mid
int sid, cnt[maxs], full[maxs], edge[maxs][maxm], best; 

inline int ID(int x, int y, bool v)    // vertical or not
{
    return x * (2*n+1) + y + n*v;
}

int full_square()
{
    for (int i = 0; i < sid; i++)
        if (cnt[i] == full[i]) return i;
    return -1;
}

void change_match(int i, int add)   // remove or add match i
{
    for (int s = 0; s < sid; s++)
        if (edge[s][i]) cnt[s] += add;
}

void init()
{
    int m, v;
    cin >> n >> m;
    int N = (n<<1)*(n+1);
    for (int i = 0; i < N; i++)
        slot[i] = true; 
    while (m--)
    {
        cin >> v;
        slot[v-1] = false;
    }
    sid = 0;
    memset(edge, 0, sizeof(edge));
    for (int k = 1; k <= n; k++)    // enumerate all square with side length k
        for (int x = 0; x <= n-k; x++)
            for (int y = 0; y <= n-k; y++)
            {
                cnt[sid] = 0, full[sid] = k << 2;
                for (int i = 0; i < k; i++)
                {
                    int l = ID(x,   y+i, false);   // left
                    int r = ID(x+k, y+i, false);   // right
                    int t = ID(x+i, y,   true);    // top
                    int b = ID(x+i, y+k, true);    // bottom
                    edge[sid][l] = edge[sid][r] = edge[sid][t] = edge[sid][b] = 1;
                    cnt[sid] += slot[l] + slot[r] + slot[t] + slot[b]; 
                }
                sid++;
            }
}

void dfs(int d)
{
    if (d >= best) return;
    int s = full_square();
    if (s == -1)
    {
        best = d;
        return;
    }
    int N = (n<<1)*(n+1);
    for (int i = 0; i < N; i++)
        if (edge[s][i])     // remove match i
        {
            change_match(i, -1);
            dfs(d+1);
            change_match(i, 1);
        }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        init();
        best = n*n;
        dfs(0);
        cout << best << endl;
    }
    return 0;
}
