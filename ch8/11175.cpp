// UVa 11175 From D to E and Back
// wangqc
#include<iostream>
#include<bitset>

using namespace std;

const int maxn = 305;
// if (x1,y)->(y,z)<-(x2,y) and (x1->y)->(y,w) but no (y,w)<-(x2,y), then not possible
int main()
{
    int n, m, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> n >> m;
        bitset<maxn> g[n];
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            g[x][y] = 1;
        }
        bool ok = true;
        for (int i = 0; ok && i < n-1; i++)
            for (int j = i+1; ok && j < n; j++)
                ok = (g[i] & g[j]).none() || (g[i] ^ g[j]).none();
        cout << "Case #" << kase << ": " << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}
