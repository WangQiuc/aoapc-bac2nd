// UVa 1153
// wangqc
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int maxn = 800005;
int n, L, D;
struct Node     // interval
{
    int q, d;
    Node() {}
    Node(int q, int d): q(q), d(d) {}
    bool operator < (const Node &rhs) const { return q < rhs.q; }
} nodes[maxn];

bool cmp(Node a, Node b) { return a.d < b.d; }

int main()
{
    int n, T;
    cin >> T;
    for (int kase = 0; kase < T; kase++)
    {
        cin >> n;
        int q, d, i = 0, t = 0, cnt = 0;
        while (i < n)
        {
            cin >> q >> d;
            if (q <= d) nodes[i++] = Node(q, d);
            else n--;
        }
        sort(nodes, nodes+n, cmp);
        priority_queue<Node> pq;
        for (int i = 0; i < n; i++)
        {
            t += nodes[i].q;
            pq.push(nodes[i]);
            cnt++;
            if (t > nodes[i].d)
            {
                Node x = pq.top(); pq.pop();
                t -= x.q;
                cnt--;
            }
        }
        if (kase) cout << endl;
        cout << cnt << endl;
    }
    return 0;
}
