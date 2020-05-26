// UVa 1607 Gates
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 200005;

int n, m;

struct Gates
{
    int a, b, o;
}gates[maxn];

int output(int k)
{
    for (int i = 1; i <= m; i++)
    {
        int a = gates[i].a;
        int b = gates[i].b;
        int va = a < 0 ? -a > k : gates[a].o;
        int vb = b < 0 ? -b > k : gates[b].o;
        gates[i].o = !(va && vb);
    }
    return gates[m].o;
}

int solve(int vn) {
  int L = 1, R = n;
  while(L < R) 
  {
    int M = L + ((R-L) >> 1);
    if(output(M) == vn) R = M; 
    else L = M+1;
  }
  return L;
}

int main() {
    int T;
    cin >> T;
    while(T--) 
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
            cin >> gates[i].a >> gates[i].b;
        int v0 = output(0);
        int vn = output(n);
        if(v0 == vn)
            for(int i = 1; i <= n; i++) cout << 0;
        else 
        {
            int x = solve(vn);
            for(int i = 1; i < x; i++) cout << 0;
            cout << "x";
            for(int i = x+1; i <= n; i++) cout << 1;
        }
        cout << endl;
    }
    return 0;
}
