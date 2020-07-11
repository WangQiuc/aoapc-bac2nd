// UVa 1648 Business Center
// wangqc
#include<iostream>

using namespace std;
const int inf = 0x3fffffff;

// x up, n-x down, ax - b(n-x) >= 1, x >= (nb+1)/(a+b), x = floor((nb+1)/(a+b))
int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        int a, b, ans = inf;
        while(m--)
        {
            cin >> a >> b;
            int x = (n*b)/(a+b) + 1;
            ans = min(ans, a*x-b*(n-x));
        }
        cout << ans << endl;
    }
    return 0;
}
