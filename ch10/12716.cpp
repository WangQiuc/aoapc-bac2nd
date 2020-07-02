// UVa 12716 GCD XOR
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int M = 30000000;
int cnt[M+1], sum[M+1];

// gcd(a,b) = c <= a-b <= a^b, if c == a^b, c == a-b == a^b, a-c == a^c
void precompute()
{
    for(int c = 1; c <= M; c++)
        for(int a = c<<1; a <= M; a += c)
            if((a^c) == (a-c)) cnt[a]++;
    for(int i = 1; i <= M; i++)
        sum[i] = sum[i-1]+cnt[i];
}

int main()
{
    precompute();
    int T, n, kase = 0;
    cin >> T;
    while(T--)
    {
        cin >> n;
        printf("Case %d: %d\n", ++kase, sum[n]);
    }
    return 0;
}
