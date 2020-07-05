// UVa 1640 The Counting Problem
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

int pow[10], cnt[10];

void init()
{
    pow[0] = 1;
    for(int i = 1; i < 9; i++)
    {
        pow[i] = pow[i-1] * 10;
        cnt[i] = pow[i-1] * i;
    }
}

// number of digit d appears in [0,n-1]
int f(int d, int x)
{
    char s[10];
    sprintf(s, "%d", x);
    int ans = 0, n = strlen(s); // digit length of x
    // count digit [1,n-1]
    for(int i = 1; i < n; i++)
    {
        if(i == 1) ans++;
        else
        {
            ans += 9 * cnt[i-1];
            if(d > 0) ans += pow[i-1];
        }
    }
    // count rest digit by digit
    int prev[10]; // d's occurence in s[:i]
    for(int i = 0; i < n; i++)
    {
        prev[i] = (s[i]-'0' == d) ? 1 : 0;
        if(i > 0) prev[i] += prev[i-1];
    }
    for(int i = 0; i < n; i++)
    {
        int lo = (i == 0 && n > 1) ? 1 : 0;         // no leading 0
        int hi = s[i] - '0' - 1;
        for(int j = lo; j <= hi; j++)
        {
            ans += cnt[n-i-1];                      // d in s[i+1:]
            if(i > 0) ans += prev[i-1]*pow[n-i-1];  // d in s[:i]
            if(j == d) ans += pow[n-i-1];           // d in s[i]
        }
    }
    return ans;
}

int main()
{
    init();
    int a, b;
    while(cin >> a >> b && a && b)
    {
        if(a > b) swap(a, b);
        for(int d = 0; d < 10; d++)
        {
            if(d) cout << " ";
            cout << f(d, b+1) - f(d, a);
        }
        cout << endl;
    }
    return 0;
}
