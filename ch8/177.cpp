// UVa 177 Paper Folding
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 8200;
// 0 - right, 1 - up, 2 - left, 3 - down
const int dx[] = {0, -1, 0, 0};
const int dy[] = {1, 0, -1, 0};
const char *mark = "_|_|";
int seq[maxn], x[maxn], y[maxn], id[maxn];

// need to adjust (x,y) e.g. (d0->d1) as "_|" need no adjust, but (d0->d3) need to set "|" under "_"
// (0,3), (2,3) -> 1
inline int adjustx(int d1, int d2) { return d2 == 3 ? (d1 & 1) ^ 1 : 0; }
// (1,0), (3,0) -> 1, (1,2), (3,2) -> -1
inline int adjusty(int d1, int d2) { return !(d2 & 1) ? (d1 & 1) * (1 - d2) : 0; }

void init_seq()
{
    seq[0] = 0, seq[1] = 1;
    for (int k = 2; k < (maxn >> 1); k <<= 1)
        for (int i = 0; i < k; i++)
            seq[i+k] = seq[i] ^ 2*(i<(k>>1));   // reverse first half and keep second half
}

bool cmp(int a, int b) { return x[a] < x[b] || (x[a] == x[b] && y[a] < y[b]); }

int main()
{
    init_seq();
    int n;
    while (cin >> n && n)
    {
        int N = 1 << n, minx = 0, miny = 0;
        x[0] = y[0] = 0;
        for (int i = 1; i < N; i++)
        {
            x[i] = x[i-1] + dx[seq[i-1]] + adjustx(seq[i-1], seq[i]);
            y[i] = y[i-1] + dy[seq[i-1]] + adjusty(seq[i-1], seq[i]);
            minx = min(minx, x[i]);
            miny = min(miny, y[i]);
        }
        for (int i = 0; i < N; i++)         // rescale to (0,0)
            x[i] -= minx, y[i] -= miny, id[i] = i;
        sort(id, id + N, cmp);              // sort id by its (x,y)
        int x0 = 0, y0 = 0;
        for (int p = 0; p < N; p++)
        {
            int i = id[p];
            if (x[i] != x0) putchar('\n'), y0 = 0;  // next line
            for (int j = y0; j < y[i]; j++) putchar(' ');
            putchar(mark[seq[i]]);                  // put mark at (x[i], y[i])
            x0 = x[i], y0 = y[i] + 1;
        }
        cout << "\n^\n";
    }
    return 0;
}
