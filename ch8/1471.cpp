// UVa 1471 Defense Lines
// wangqc
#include<iostream>
#include<set>

using namespace std;

const int maxn = 200005;
int n, a[maxn], f[maxn], g[maxn];

struct Node
{
    int a, g;
    Node(int a, int g): a(a), g(g) {}
    bool operator < (const Node &rhs) const { return a < rhs.a; }
};

set<Node> s;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        if (n == 1) { cout << "1\n"; continue; }
        // g[i] is the length of longest increasing subarray finish at i;
        g[0] = 1;
        for (int i = 1; i < n; i++) 
            g[i] = a[i-1] < a[i] ? g[i-1] + 1 : 1;
        
        // f[i] is the length of longest increasing subarray start at i;
        f[n-1] = 1;
        for (int i = n-2; i >= 0; i--)
            f[i] = a[i] < a[i+1] ? f[i+1] + 1 : 1;   
        
        s.clear(); s.insert(Node(a[0], g[0]));
        int maxlen = 1;
        for (int i = 1; i < n; i++)
        {
            Node x(a[i], g[i]);
            auto it = s.lower_bound(x);     // smallest node that >= x.a
            bool keep = true;
            if (it != s.begin())
            {   // largest node y that y.a < x.a so can make an increasing seq;
                Node y = *(--it); 
                maxlen = max(maxlen, f[i] + y.g);
                // x contributes less than y/it so no need to keep
                if ((x.a == it->a && x.g <= it->g) || x.g <= y.g) keep = false;
            }
            if (keep)
            {
                s.erase(x); s.insert(x);  // update (x.a, x.old_g) to (x.a, x.g)
                it = ++s.find(x);
                while (it != s.end() && it->a > x.a && it->g <= x.g) s.erase(it++);
            }
        }
        cout << maxlen << endl;
    }
    return 0;
}
