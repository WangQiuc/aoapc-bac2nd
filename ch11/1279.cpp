// UVa 1279 Asteroid Rangers
// wangqc

#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 55;
const int maxs = maxn * (maxn+1) / 2;
const double eps = 1e-8;

int n, s;

struct Event 
{
    double t;
    int s, s0; // After event, new segment s will be smaller than the old segment s0
    Event(double t=0, int s=0, int s0=0) : t(t), s(s), s0(s0) {}
    bool operator < (const Event& rhs) const { return t - rhs.t < 0; }
};
vector <Event> events;

struct Motion 
{
    double x, y, z;
    double dx, dy, dz;
    void read() { scanf("%lf%lf%lf%lf%lf%lf", &x, &y, &z, &dx, &dy, &dz); }
} motion[maxn];

struct Segment 
{
    double a, b, c;
    int x, y;
    bool operator < (const Segment& rhs) const { return c - rhs.c < 0; }
} seg[maxs];

inline double sqr(double x) { return x * x; }

// union-find
int p[maxn];

void init_uf() { for(int i = 0; i < n; i++) p[i] = i; }
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x; }

void gen_segments() 
{
    s = 0;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++, s++) 
        {
            int xij = motion[i].x-motion[j].x, yij = motion[i].y-motion[j].y, zij = motion[i].z-motion[j].z;
            int dxij = motion[i].dx-motion[j].dx, dyij = motion[i].dy-motion[j].dy, dzij = motion[i].dz-motion[j].dz;
            seg[s].a = sqr(dxij) + sqr(dyij) + sqr(dzij);
            seg[s].b = 2*(xij*dxij + yij*dyij + zij*dzij);
            seg[s].c = sqr(xij) + sqr(yij) + sqr(zij);
            seg[s].x = i;
            seg[s].y = j;
        }
    sort(seg, seg + s);
}

void gen_events() 
{
    events.clear();
    for(int i = 0; i < s; i++)
        for(int j = i+1; j < s; j++) 
        {
            int s1 = i, s2 = j; 
            if (seg[s1].a - seg[s2].a < 0) 
                s1 = j, s2 = i;
            double a = seg[s1].a - seg[s2].a;
            double b = seg[s1].b - seg[s2].b;
            double c = seg[s1].c - seg[s2].c;
            if(fabs(a) < eps) 
            { // bt + c = 0
                if (fabs(b) < eps) continue; // no solution
                if (b > 0) { swap(s1, s2); b = -b; c = -c; } // bt + c = 0, b < 0
                if (c > 0) events.push_back(Event(-c/b, s1, s2)); // t > 0
                continue;
            }
            double delta = b*b - 4*a*c;
            if (delta < eps) continue; // no solution
            delta = sqrt(delta);
            double t1 = -(b+delta) / (2*a); // solution 1
            double t2 = (delta-b) / (2*a);  // solution 2
            if (t1 > 0) events.push_back(Event(t1, s1, s2)); // steep one will be smaller
            if (t2 > 0) events.push_back(Event(t2, s2, s1)); // flat one will be smaller
        }
    sort(events.begin(), events.end());
}

int solve() 
{
    int pos[maxs]; 
    int e[maxn];

    // initial MST
    init_uf();
    for(int i = 0; i < s; i++) pos[i] = 0;
    int idx = 0;
    for(int i = 0; i < s; i++) 
    {
        int x = find(seg[i].x), y = find(seg[i].y);
        if (x != y) 
            e[pos[i] = ++idx] = i, p[x] = y;
        if(idx == n-1) break;
    }

    int cnt = 1;
    for(int i = 0; i < events.size(); i++) if(pos[events[i].s0] && (!pos[events[i].s])) 
    {
        init_uf();
        int p0 = pos[events[i].s0];
        for(int j = 1; j < n; j++) if (j != p0)
        {
            int x = find(seg[e[j]].x), y = find(seg[e[j]].y);
            if(x != y) p[x] = y;
        }
        int x = find(seg[events[i].s].x), y = find(seg[events[i].s].y);
        if(x != y) 
        {
            // new MST found! now replace oldks with newks
            cnt++;
            pos[events[i].s] = p0;
            e[p0] = events[i].s;
            pos[events[i].s0] = 0;
        }
    }
    return cnt;
}

int main() 
{
    int kase = 0;
    while(scanf("%d", &n) == 1) 
    {
        for(int i = 0; i < n; i++) motion[i].read();
        gen_segments();
        gen_events();
        printf("Case %d: %d\n", ++kase, solve());
    }
    return 0;
}
