// UVa 1646 Edge Case
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int M = 1000000000;
int d[10002][240];

// f(n) = f(n-1) + f(n-2) (not choose node 0 + choose node 0, cannot choose neighbor two nodes)
void init()
{   // d[i][0] digit length of f(i), d[i][j] jth least significant 9-digits of f(i)
    d[1][0] = d[2][0] = 1;  
    d[1][1] = 1, d[2][1] = 3;
    for(int i = 3; i <= 10000; i++)
    {
        int carry = 0;
        d[i][0] = d[i-1][0];
        for(int j = 1; j <= d[i-1][0]; j++)
        {
            carry += d[i-1][j] + d[i-2][j];
            d[i][j] = carry % M, carry /= M;
        }
        if(carry) d[i][++d[i][0]] = carry;
    }
}

int main()
{
    init();
    int n;
    while(cin >> n)
    {
        cout << d[n][d[n][0]];  // first 9 digits has no leading 0
        for(int i = d[n][0]-1; i; i--)
            printf("%09d", d[n][i]);
        cout << endl;
    }
    return 0;
}
