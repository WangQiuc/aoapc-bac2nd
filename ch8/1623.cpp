// UVa 1623 Enter The Dragon
// wangqc
#include<iostream>
#include<cstring>
#include<set>

using namespace std;

const int maxn = 1000005;
// day i rains at lake rain[i], lake i previously full on day full[i]
int rain[maxn], full[maxn], ans[maxn]; 

int main()
{
    int n, m, T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        set<int> drink; // days dragon can drink
        bool ok = true;
        memset(ans, 0 ,sizeof(ans));
        memset(full, 0 ,sizeof(full));
        for (int i = 0; i < m; i++) cin >> rain[i];
        for (int i = 0; ok && i < m; i++)
        {
            if (rain[i]) 
            {
                ans[i] = -1;
                auto it = drink.lower_bound(full[rain[i]]);
                if (it == drink.end()) ok = false;
                else ans[*it] = rain[i], full[rain[i]] = i, drink.erase(it); 
            }
            else drink.insert(i);
        }
        if (ok) 
        {
            cout << "YES" << endl;
            bool first = true;
            for (int i = 0; i < m; i++) if (ans[i] != -1)
            {
                if (first) first = false;
                else cout << " ";
                cout << ans[i];
            }
            cout << endl;
        }
        else cout << "NO" << endl;
    }
    return 0;
}
