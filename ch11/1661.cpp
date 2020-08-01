// UVa 1661 Equation
// wangqc
#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>

using namespace std;

typedef long long ll;
const int maxn = 500;
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

struct Fraction
{
    ll p, q;
    Fraction(ll p=0, ll q=1): p(p), q(q) {}
    void normalize(ll &p, ll &q) { ll g = gcd(p, q); p /= g, q/= g; }
    Fraction operator = (ll x) { p = x, q = 1; return *this; }
    Fraction operator - () { return {-p, q}; }
    Fraction operator + (Fraction &rhs) 
    { 
        ll x, y;
        x = p*rhs.q + q*rhs.p;
        y = q*rhs.q;
        normalize(x, y);
        return {x, y};
    }
    Fraction operator - (Fraction &rhs) { return (-rhs) + *this; }
    Fraction operator * (Fraction &rhs) 
    { 
        ll x, y;
        x = p * rhs.p;
        y = q * rhs.q;
        normalize(x, y);
        return {x, y};
    }
    Fraction operator / (Fraction &rhs) { return Fraction(rhs.q, rhs.p) * (*this); }
    bool operator == (const Fraction &rhs) const { return p * rhs.q == q * rhs.p; }
    bool operator < (Fraction &rhs) { return p * rhs.q < q * rhs.p; }
    void print()
    {
        if(q < 0) q = -q, p = -p;
        printf("X = %lld/%lld\n", p, q);
    }
};

struct Node
{
    Node *l, *r;
    Fraction val;
    char op;
    bool vis;
    Node() {};
    Node(Fraction &v, Node *l = NULL, Node *r = NULL): val(v), l(l), r(r) {};
} tree[maxn];

bool is_op[256];
char rev[256];
Fraction ans;

Fraction calculate(Fraction &x, Fraction &y, char op)
{
    switch(op)
    {
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': return x / y;
    }
    return {0, 1};
}

void calculate_rev(Fraction &x, char op)
{
    switch(op)
    {
        case '+': ans = ans - x; return;
        case '-': ans = x - ans; return;
        case '*': ans = ans / x; return;
        case '/': ans = x / ans; return;
    }
}

bool dfs(Node *x)
{
    if(x->l == NULL) return true;
    if(x->l->vis)
    {
        ans = calculate(ans, x->r->val, rev[x->op]);
        if(!dfs(x->l)) return false;
    }
    else
    {
        calculate_rev(x->l->val, x->op);
        if(ans.q == 0 || !dfs(x->r)) return false;
    }
    return true;
}

Node *read(char ch)
{
    int cnt = 0;
    stack<Node *> s;
    do
    {
        while(ch == ' ') ch = getchar();
        Node &curr = tree[cnt];
        if(is_op[ch])
        {
            curr.op = ch;
            curr.r = s.top(); s.pop();
            curr.l = s.top(); s.pop();
            curr.vis = curr.l->vis ||curr.r->vis;
            if(curr.vis)
            {
                if((curr.op == '*' && (curr.r->vis ? curr.l->val == 0 : curr.r->val == 0))
                || (curr.op == '/' && curr.r->vis && curr.l->val == 0))
                    curr.vis = false, curr.val = 0, curr.l = curr.r = NULL;
            }
            else
            {
                curr.val = calculate(curr.l->val, curr.r->val, curr.op);
                curr.l = curr.r = NULL;
            }
        }
        else
        {
            if(ch == 'X')
                curr.vis = true;
            else
            {
                curr.vis = false;
                int v = ch - '0';
                while(ch = getchar(), ch >= '0' && ch <= '9')
                    v = v*10 + ch-'0';
                curr.val = v;
            }
            curr.l = curr.r = NULL;
        }
        s.push(tree+cnt);
        ch = getchar();
        cnt++;
    } while (ch != '\n' && ~ch);
    return s.top();
}

int main()
{
    is_op['+'] = is_op['-'] = is_op['*'] = is_op['/'] = true;
    rev['+'] = '-', rev['-'] = '+', rev['*'] = '/', rev['/'] = '*';
    char head;
    while(~(head = getchar()))
    {
        Node *root = read(head);
        if(!root->vis)
        {
            if(root->val == 0) puts("MULTIPLE");
            else puts("NONE");
        }
        else
        {
            ans = 0;
            if(dfs(root)) ans.print();
            else puts("NONE");
        } 
    }
    return 0;
}
