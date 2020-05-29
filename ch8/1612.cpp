// UVa 1612 Guess
// wangqc
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxn = 16400;
const double eps = 1e-8;
int id[maxn];   // id[i], rank i's player ID

inline int dcmp(double a, double b)
{
    if (fabs(a - b) < eps) return 0;
    return a < b ? -1 : 1;
}

struct Node
{
    double a, b, c, s;
    double cand[6];
    void read()
    {
        cin >> a >> b >> c;
        s = a + b + c;
        cand[0] = a, cand[1] = b, cand[2] = c, cand[3] = a+b, cand[4] = b+c, cand[5] = a+c;
        sort(cand, cand+6, greater<double>()); 
    }
}score[maxn];   // score[i].s, proposed score for rank i's player

// rank i's score s is valid: lower score or equal score and larger id
bool valid(int i, double s)
{ 
    return dcmp(score[id[i-1]].s, s) == 1 || 
    (dcmp(score[id[i-1]].s, s) == 0 && id[i-1] < id[i]);
}

int main()
{
    int n, kase = 0;
    while (cin >> n && n)
    {
        for (int i = 1; i <= n; i++) 
            score[i].read();
        for (int i = 0; i < n; i++)
            cin >> id[i];
        bool ok = true;
        for (int i = 1; ok && i < n; i++) if (!valid(i, score[id[i]].s))
        {   
            ok = false;
            for (double s : score[id[i]].cand)  // try to find a valid s for i
                if ((ok = valid(i, s)))
                {   score[id[i]].s = s; break; }
        }
        if (ok) printf("Case %d: %.2lf\n", ++kase, score[id[n-1]].s);
        else printf("Case %d: No solution\n", ++kase);
    }
    return 0;
}
