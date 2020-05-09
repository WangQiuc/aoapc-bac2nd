// UVa221 Urban Elevations
// wangqc

#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 105;
struct Building
{
    int id;
    double x, y, w, d, h;
    bool operator < (const Building &rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

} b[maxn];

int n, m;
double x[maxn * 2];

bool cover(int i, double x)
{
    return b[i].x <= x && b[i].x + b[i].w >= x;
}

bool visible_at_x(int i, double x)
{
    if(!cover(i, x)) return false;
    for (int k = 0; k < n; k++)
        if (b[k].y < b[i].y && b[k].h >= b[i].h && cover(k, x)) return false;
    return true;
}

bool visible(int i)
{
    for (int k = 0; k < m-1; k++)
        if (visible_at_x(i, (x[k]+x[k+1])/2)) return true;
    return false;
}

int main()
{
    int kase = 0;
    while (scanf("%d", &n) == 1 && n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf%lf", &b[i].x, &b[i].y, &b[i].w, &b[i].d, &b[i].h);
            b[i].id = i + 1;
            x[i*2] = b[i].x;
            x[i*2+1] = b[i].x + b[i].w; 
        }
        sort(b, b + n);
        sort(x, x + n*2);
        m = unique(x, x + n*2) - x;
        
        if (kase) printf("\n");
        printf("For map #%d, the visible buildings are numbered as follows:\n%d", ++kase, b[0].id);
        for (int i = 1; i < n; i++)
            if (visible(i)) printf(" %d", b[i].id);
        printf("\n");
    }
    return 0;
}
