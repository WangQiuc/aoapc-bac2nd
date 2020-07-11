// UVa 766 Sum of powers
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;

const int maxn = 25;
int n;
// Bernoulli polynomials 
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }

struct Fraction
{
    ll a, b;    // a/b
    Fraction(ll a=0, ll b=1): a(a), b(b) { reduce(); }
    void reduce()
    {
        if(b < 0) a = -a, b = -b;
        long long g = gcd(a, b);
        if(g < 0) g = -g;
        a /= g, b /= g;
    }

    Fraction operator + (const Fraction &rhs)
    {
        ll y = lcm(b, rhs.b);
        ll x = y / b * a + y / rhs.b * rhs.a;
        return Fraction(x, y);
    }

    Fraction operator - (const Fraction &rhs)
    {
        ll y = lcm(b, rhs.b);
        ll x = y / b * a - y / rhs.b * rhs.a;
        return Fraction(x, y);
    }

    Fraction operator * (const Fraction &rhs)
    {
        return Fraction(a*rhs.a, b*rhs.b);
    }

    Fraction operator / (const Fraction &rhs)
    {
        return Fraction(a*rhs.b, b*rhs.a);
    }
};

Fraction C[maxn][maxn], B[maxn], ans[maxn];

void init()
{
    for(int i = 0; i < maxn; i++)
        C[i][0] = C[i][i] = Fraction(1, 1);
    for(int i = 2; i < maxn; i++)
        for(int j = 1; j < i; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    B[0] = Fraction(1, 1);
    for(int i = 1; i < maxn-2; i++)
    {
        for(int j = 0; j < i; j++)
            B[i] = B[i] + C[i+1][j] * B[j];
        B[i] = B[i] * Fraction(-1ll, i+1ll);
    }
}

int main()
{
    init();
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        ll m = 1;
        for(int i = 1; i <= n+1; i++)
        {
            ans[i] = C[n+1][i] * B[n+1-i]*Fraction(1ll, n+1ll);
            m = lcm(m, ans[i].b);
        }
        ans[n] = ans[n] + Fraction(1ll, 1ll);
        cout << m;
        for(int i = n+1; i > 0; i--)
            cout << " " << m/ans[i].b * ans[i].a;
        cout << " 0" << endl;
        if(T) cout << endl;
    }
    return 0;
}
