// UVa 10288 Coupons
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
// E(time) to get a new coupon when already get k coupons: (1-s)Σ(xs^(x-1)) = n/(n-k)
// s = k/n, x times to get a new one s^(x-1)*(1-s), Σ(xs^(x-1)) = 1/(1-s)^2
typedef long long LL;

LL gcd(LL a, LL b) { return b ? gcd(b, a%b) : a; }

LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

int get_len(LL x)
{
    int len = 0;
    while(x)
        x /= 10, len++;
    return len;
}

void print_kchars(int k, char ch) { while(k--) cout << ch; }

void print(LL a, LL b, LL c)
{
    if(!b) cout << a << endl;
    else
    {
        int k = get_len(a) + 1;
        print_kchars(k, ' '), cout << b << endl;
        cout << a << " ", print_kchars(get_len(c), '-'), cout << endl;
        print_kchars(k, ' '), cout << c << endl;
    }
    
}

int main()
{
    int n;
    while(cin >> n && n)
    {
        if(n == 1) print(1, 0, 0);
        else
        {
            LL c = 1, b = 0;
            for(int i = 2; i <= n-1; i++)
                c = lcm(c, i);
            for(int i = 2; i <= n-1; i++)
                b += c / i;
            b *= n;
            // ans = b / c
            LL g = gcd(b, c);
            b /= g, c /= g;
            LL a = 1 + n + b / c;
            b %= c;
            print(a, b, c);
        }
        
    }
    return 0;
}
