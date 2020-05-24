// UVa 11134 Fabled Rooks
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 5001;
int n, x1[maxn], x2[maxn], y1[maxn], y2[maxn], x[maxn], y[maxn];

// place c[i] between [a[i], b[i]] for all i from 1 to n
bool solve(int *a, int *b, int *c, int n)
{
    fill(c, c+n, -1);
    for (int slot = 1; slot <= n; slot++)
    {   // try to place jth rook (with smallest b[i] that can hold x: a[i] <= x <= b[i]) at x
        int j = -1, minb = n+1;
        for (int i = 0; i < n; i++) if (c[i] == -1 && slot >= a[i] && b[i] < minb)
            j = i, minb = b[i];
        if (j == -1 || slot > minb) return false;
        c[j] = slot;
    }
    return true;
}

int main()
{
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        if (solve(x1, x2, x, n) && solve(y1, y2, y, n))
            for (int i = 0; i < n; i++) cout << x[i] << " " << y[i] << endl;
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
