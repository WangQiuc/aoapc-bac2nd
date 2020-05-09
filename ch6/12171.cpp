// UVa12171 Sculpture
// wangqc

#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

const int maxn = 55;
const int maxd = 1005;
const int space = maxd * maxd * maxd;

int n, x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];
int nx, ny, nz;
int xs[maxn<<1], ys[maxn<<1], zs[maxn<<1];

const int dx[] = {-1,1,0,0,0,0};
const int dy[] = {0,0,-1,1,0,0};
const int dz[] = {0,0,0,0,-1,1};
int graph[maxn<<1][maxn<<1][maxn<<1];

struct Cell
{
    int x, y, z;
    Cell(int x, int y, int z): x(x), y(y), z(z) {}
    bool valid() const { return x >= 0 && x < nx-1 && y >= 0 && y < ny-1 && z >= 0 && z < nz-1; }
    bool solid() const { return graph[x][y][z] == 1; }
    bool isvis() const { return graph[x][y][z] == 2; }
    void visit() const { graph[x][y][z] = 2; }
    Cell neighbor(int d) const { return Cell(x+dx[d], y+dy[d], z+dz[d]); }
    int volume() const { return (xs[x+1]-xs[x])*(ys[y+1]-ys[y])*(zs[z+1]-zs[z]); }
    int area(int d) const 
    { 
        if (dx[d]) return (ys[y+1]-ys[y])*(zs[z+1]-zs[z]);
        else if (dy[d]) return (xs[x+1]-xs[x])*(zs[z+1]-zs[z]);
        else return (xs[x+1]-xs[x])*(ys[y+1]-ys[y]); 
    }
};

void discretize(int *x, int &n)
{
    sort(x, x+n);
    n = unique(x, x+n) - x;
}

int ID(int *x, int n, int x0) { return lower_bound(x, x+n, x0) - x; }

void bfs(int &s, int &v)
{
    s = 0, v = 0;
    Cell x(0, 0, 0);
    x.visit();
    queue<Cell> q;
    q.push(x);
    while (!q.empty())
    {
        x = q.front(); q.pop();
        v += x.volume();
        for (int d = 0; d < 6; d++)
        {
            Cell y = x.neighbor(d);
            if (!y.valid()) continue;
            if (y.solid()) s += y.area(d);
            else if (!y.isvis())
            {
                y.visit();
                q.push(y);
            }
        }
    }
    v = space - v;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        xs[0] = ys[0] = zs[0] = 0;
        xs[1] = ys[1] = zs[1] = maxd;
        nx = ny = nz = 2;
        cin >> n;
        for (int i  = 0; i < n; i++)
        {
            cin >> x0[i] >> y0[i] >> z0[i] >> x1[i] >> y1[i] >> z1[i];
            x1[i] += x0[i], y1[i] += y0[i], z1[i] += z0[i];
            xs[nx++] = x0[i], xs[nx++] = x1[i];
            ys[ny++] = y0[i], ys[ny++] = y1[i];
            zs[nz++] = z0[i], zs[nz++] = z1[i];
        }
        discretize(xs, nx), discretize(ys, ny), discretize(zs, nz);
        memset(graph, 0, sizeof(graph));
        for (int i = 0; i < n; i++)
        {
            int X0 = ID(xs, nx, x0[i]), X1 = ID(xs, nx, x1[i]);
            int Y0 = ID(ys, ny, y0[i]), Y1 = ID(ys, ny, y1[i]);
            int Z0 = ID(zs, nz, z0[i]), Z1 = ID(zs, nz, z1[i]);
            for (int x = X0; x < X1; x++)
                for (int y = Y0; y < Y1; y++)
                    for (int z = Z0; z < Z1; z++)
                        graph[x][y][z] = 1;
        }
        int s, v;
        bfs(s, v);
        cout << s << " " << v << endl;
    }
    return 0;
}
