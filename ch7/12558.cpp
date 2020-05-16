// UVa 12558 Egyptian Fractions
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long LL;
const int maxn = 10005;
int maxd;
LL seq[maxn], v[maxn];
bool block[1001];

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a%b); }

inline int get_first(LL a, LL b) 
{ 
    int i = b/a + 1;
    return i; 
}

bool better(int d)
{
    for (int i = d; i >= 0; i--)
        if (v[i] != seq[i])
            return seq[i] == -1 || v[i] < seq[i];
    return false;
}

bool dfs(int d, int i, LL aa, LL bb)
{   // current depth d, sum == aa / bb, start from src
    if (d == maxd)
    {
        if (bb % aa || ((v[d] = bb / aa) <= 1000 && block[v[d]])) return false;
        if (better(d)) memcpy(seq, v, sizeof(LL) * (d+1));
        return true;
    }
    bool ok = false;
    i = max(i, get_first(aa, bb));
    for (;;i++)
    {
        while (i <= 1000 && block[i]) i++;
        if (bb * (maxd + 1 - d) <= i * aa) break;  // rest_d * (1/i) <= aa / bb, no solution
        v[d] = i;
        LL b = bb * i;
        LL a = aa * i - bb;
        LL g = gcd(a, b);
        if (dfs(d+1, i+1, a/g, b/g)) ok = true;
    }
    return ok;
}

int main()
{
    int a, b, n, x, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> a >> b >> n;
        memset(block, 0, sizeof(block));
        while (n--) 
        {   cin >> x; block[x] = true; }
        bool ok = false;
        for (maxd = 1; maxd <= maxn; maxd++)
        {
            memset(seq, -1, sizeof(seq));
            if (dfs(0, get_first(a, b), a, b)) { ok = true; break; };
        }
        cout << "Case " << kase << ": ";
        if (ok)
        {
            cout << a << "/" << b << "=";
            for (int i = 0; i < maxd; i++) cout << "1/" << seq[i] << "+";
            cout << "1/" << seq[maxd] << endl;
        }
        else cout << "No solution.\n";
    }
    return 0;
}
