// UVa 1647 Computer Transformation
// wangqc
#include<iostream>
#include<cstring>

using namespace std;
const int maxn = 1000, maxk = 35, M = 1000000000;
int a[maxn+2][maxk+2];     // a[i][x] = xth 9 digits of f(i)
// pattern y = ~x, ~(xy) = yx, xy -> yxxy;
// after 2 steps, pattern unit is 0110 / 1001, x = 0110, y = 1001
// f(yxxy)=2f(xy)+1 as xx produce a new "00", and f(xyyxyxxy)=2f(yxxy)-1 as it won't duplicate "00" from xx
// f(i+1) = 2f(i) + (i&1 ? 1 : -1)
void init()
{
    a[1][0] = 1, a[1][1] = 0;
    for(int i = 1; i < maxn; i++)
    {   // a[i][0] stores digit length of f(i)
        int n = (a[i+1][0] = a[i][0]), carry = i&1 ? 1 : -1;
        for(int j = 1; j <= n; j++)
        {
            carry += a[i][j] << 1;
            a[i+1][j] = (carry + M) % M, carry /= M;
        }
        if(carry) a[i+1][++a[i+1][0]] = carry;
    }
}

int main()
{
    init();
    int n;
    while(cin >> n)
    {
        cout << a[n][a[n][0]];      // first 9 digits has no leading 0
        for(int i = a[n][0]-1; i; i--)
            printf("%09d", a[n][i]);
        cout << endl;
    }
    return 0;
}
