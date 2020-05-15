// UVa 1602 Lattice Animals
// wangqc
#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int maxn = 10, MINV = 20;
struct Cell
{
    int x, y;
    Cell(int x=0, int y=0): x(x), y(y) {};
    bool operator < (const Cell &rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y); 
    }
};
typedef set<Cell> Polyomino;

inline Polyomino normalize(const Polyomino &p)
{
    int minX = MINV, minY = MINV;
    for (auto c : p)
        minX = min(minX, c.x), minY = min(minY, c.y);
    Polyomino pn;
    for (auto c : p)
        pn.insert(Cell(c.x - minX, c.y - minY));
    return pn;
}

inline Polyomino rotate(const Polyomino &p)
{
    Polyomino pr;
    for (auto c : p)
        pr.insert(Cell(c.y, -c.x));
    return normalize(pr);
}

inline Polyomino flip(const Polyomino &p)
{
    Polyomino pr;
    for (auto c : p)
        pr.insert(Cell(c.x, -c.y));
    return normalize(pr);
}

set<Polyomino> poly[maxn + 1];     // poly[x] collections of x-cell polyominoes
int db[maxn+1][maxn+1][maxn+1];    // precomputing and store answer in database

void insert_cell(const Polyomino &p0, const Cell &c)
{
    Polyomino p = p0;
    p.insert(c);
    p = normalize(p);
    int n = p.size();
    for (int i = 0; i < 4; i++)
    {
        if (poly[n].count(p)) return;
        p = rotate(p);
    }
    p = flip(p);
    for (int i = 0; i < 4; i++)
    {
        if (poly[n].count(p)) return;
        p = rotate(p);
    }
    poly[n].insert(p);
}

void preprocess()
{
    Polyomino s;
    s.insert(Cell());
    poly[1].insert(s);
    for (int n = 2; n <= maxn; n++)
        for (auto p : poly[n-1])
            for (auto c : p)
                for (int d = 0; d < 4; d++)
                {
                    Cell nc(c.x + dx[d], c.y + dy[d]);
                    if (!p.count(nc)) insert_cell(p, nc);
                }
    for (int n = 1; n <= maxn; n++)
        for (int w = 1; w <= maxn; w++)
            for (int h = 1; h <= maxn; h++)
            {
                int cnt = 0;
                for (auto p : poly[n])
                {
                    int maxX = 0, maxY = 0;
                    for (auto c : p)
                        maxX = max(maxX, c.x), maxY = max(maxY, c.y);
                    if (min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w))
                        cnt++;
                }
                db[n][w][h] = cnt;
            }
}

int main()
{
    preprocess();
    int n, w, h;
    while (cin >> n >> w >> h)
        cout << db[n][w][h] << endl;
    return 0;
}
