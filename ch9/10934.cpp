// UVa 10934 Dropping water balloons 
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxk = 101;
const int maxt = 64;

unsigned long long dp[maxk][maxt];  //  dp[k][t] highest floor tested by k eggs and t trials

int main()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < maxk; i++)
        for (int j = 1; j < maxt; j++)
            dp[i][j] = dp[i-1][j-1]+1 + dp[i][j-1];
    int k, t;
    unsigned long long n;
    while (cin >> k >> n && n)
    {
        for (t = 1; t < maxt; t++) 
            if (dp[k][t] >= n) break;
        
        if (t == maxt) cout << "More than 63 trials needed.\n";
        else cout << t << endl;
    }
    return 0;
}
