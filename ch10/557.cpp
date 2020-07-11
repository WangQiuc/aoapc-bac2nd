// UVa 557 Burger
// wangqc
#include<iostream>

using namespace std;
const int maxn = 50000;
// p[n] last two children eat different burgers: C(2n-2,n-1) * (1/2)^(2n-2)
// p[n+1] = (2n-1)/2n * p[n]
double p[maxn+5];

void init()
{
    p[1] = 1;
    for(int i = 1; i <= maxn; i++)
        p[i+1] = p[i]*((i<<1)-1)/(i<<1);
}

int main()
{
    init();
    int T, n;
    cin >> T;
    while(T--)
    {
        cin >> n;
        printf("%.4f\n", 1-p[n>>1]);
    }
    return 0;
}
