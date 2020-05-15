// UVa 12325 Zombie's Treasure Chest
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

typedef long long LL;
const int LIMIT = 1 << 16;

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        int n, s1, v1, s2, v2;
        cin >> n >> s1 >> v1 >> s2 >> v2;
        if (s1 > s2) { swap(s1, s2); swap(v1, v2); }
        LL maxv = 0;
        if (n / s2 > LIMIT)
        {
            for (LL i = 0; i <= s1; i++)
                maxv = max(maxv, i*v2 + (n-s2*i)/s1*v1);  // do division first, need floor count
            for (LL i = 0; i <= s2; i++)
                maxv = max(maxv, i*v1 + (n-s1*i)/s2*v2);            
        }
        else for (LL i = 0; s2*i <= n; i++)
            maxv = max(maxv, i*v2 + (n-s2*i)/s1*v1);
        cout << "Case #" << kase << ": " << maxv << endl;
    }
    return 0;
}
