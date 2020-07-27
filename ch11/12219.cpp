// UVa 12219 Common Subexpression Elimination
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<map>

using namespace std;

const int maxn = 60000;
int T, kase, cnt, vis[maxn];
char expr[maxn*5], *p;

struct Node
{
    string s;
    int v, l, r;
    bool operator < (const Node &rhs) const // key = (node.char, left.id, right.id)
    {
        if(v != rhs.v) return v < rhs.v;
        if(l != rhs.l) return l < rhs.l;
        return r < rhs.r;
    }
} nodes[maxn];

map<Node, int> db;

int dfs()
{
    int id = cnt++;
    Node &x = nodes[id];
    x.l = x.r = -1;
    x.s = "", x.v = 0;
    while(isalpha(*p))
    {
        x.v = x.v*27+(*p-'a'+1);
        x.s.push_back(*p);
        p++;
    }
    if(*p == '(') p++, x.l = dfs(), p++, x.r = dfs(), p++;
    if(!db.count(x)) return db[x] = id;
    id--; cnt--; 
    return db[x];
}

void print(int i)
{
    if(vis[i] == kase) cout << i+1;
    else
    {
        vis[i] = kase;
        cout << nodes[i].s;
        if(nodes[i].l != -1)
        {
            cout << "(";
            print(nodes[i].l);
            cout << ",";
            print(nodes[i].r);
            cout << ")";
        }
    }
}

int main()
{
    cin >> T;
    for(kase = 1; kase <= T; kase++)
    {
        db.clear();
        cnt = 0;
        cin >> expr;
        p = expr;
        print(dfs());
        cout << endl;
    }
    return 0;
}
