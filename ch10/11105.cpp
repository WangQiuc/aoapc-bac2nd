// UVa 11105 Semi-prime H-numbers
// wangqc
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 1000001;
int h[maxn+5];   // 0: hprime, 1: hsemiprime, -1: h-composite

void init()
{
    for(int i = 5; i <= maxn; i += 4)
        for(int j = 5; j <= maxn; j += 4)
        {
            int x = i*j;
            if(x > maxn) break;
            h[x] = (h[i] || h[j]) ? -1 : 1;
        }
    for(int i = 2; i <= maxn; i++)
        h[i] = h[i-1] + (h[i] == 1);
}

int main()
{
    init();
    int n;
    while(cin >> n && n)
        cout << n << " " << h[n] << endl;
    return 0;
}
