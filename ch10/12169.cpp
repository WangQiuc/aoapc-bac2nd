// UVa 12169 Disgruntled Judge
// wangqc
#include<iostream>

using namespace std;

const int maxn = 10005, M = 10001;
int T, x[maxn];

inline int f(int a, int b, int x) { return (a*x + b) % M; }

void solve()
{
    for(int a = 0; a < M; a++)
        for(int b = 0; b < M; b++)
        {
            bool ok = true;
            for(int i = 2; ok && i < T*2; i += 2)
            {
                x[i] = f(a, b, x[i-1]);
                ok = x[i+1] == f(a, b, x[i]);
            }
            if(ok) { x[2*T] = f(a, b, x[2*T-1]); return; }
        }
}

int main()
{
    while(cin >> T)
    {
        for(int i = 1; i < T*2; i += 2)
            cin >> x[i];
        solve();
        for(int i = 2; i <= T*2; i+= 2)
            cout << x[i] << endl;
    }
    return 0;
}
