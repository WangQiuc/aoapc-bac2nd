// UVa 12520 Square Garden
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
typedef long long ll;
ll d, n, a, b, c, cnt;

// isolated block: +4   -- a
// corner block: +2-2   -- b
// border block: +1-3   -- c
// inner block:  +0-4   -- n-a-b-c
ll count()
{
    if(n <= a) return n<<2;
    if(n <= a+b) return a<<2;
    if(n <= a+b+c) return (a<<2) - ((n-a-b)<<1);
    return (a<<2) - (c<<1) - ((n-a-b-c)<<2);
}

int main()
{
    while(cin >> d >> n && d)
    {
        if(d & 1)
        {
            a = (d*d>>1)+1;
            b = 0;
            c = (d-1)>>1<<2;
            cnt = count();  // count corner block in a
            a = d*d>>1;
            b = d == 1 ? 1 : 4;
            c = d ? (d-3)>>1<<2 : 0;
            cnt = max(cnt, count());
        }
        else
        {
            a = d*d>>1;
            b = 2;
            c = ((d>>1)-1)<<2;
            cnt = count();
        }
        cout << cnt << endl;
    }
    return 0;
}
