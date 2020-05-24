// UVa 11054 Wine trading in Gergovia
// wangqc
#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    int n, x;
    while (cin >> n && n)
    {
        long long agg = 0, k = 0;
        while (n--)
        {
            cin >> x;
            agg += x;
            k += abs(agg);
        }
        cout << k << endl;
    }
    return 0;
}
