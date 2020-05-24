// UVa 11093 Just Finish it up
// wangqc
#include<iostream>

using namespace std;

const int maxn = 100005;
int a[maxn];  // a[i] = petrol[i] - cost[i]

int main()
{
    int n, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cout << "Case " << kase << ": ";
        cin >> n;
        int x, s = 0;
        for (int i = 0; i < n; i++)
        {   cin >> a[i]; s += a[i]; }
        for (int i = 0; i < n; i++)
        {   cin >> x; a[i] -= x, s -= x; }
        if (s < 0) cout << "Not possible\n";
        else
        {   // return the leftmost index that can reach n
            int agg = 0, start = 0;
            for (int i = 0; i < n; i++)
            {
                agg += a[i];
                if (agg < 0) start = i+1, agg = 0;
            }
            cout << "Possible from station " << start+1 << endl;
        }
    }
    return 0;
}
