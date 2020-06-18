// UVa 242 Stamps and Envelope Size
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 25, maxv = 1005;;
const int INF = 0x3f3f3f3f;

int s, n, a[maxn], d[maxv], ans[maxn];

int main()
{
    while (cin >> s && s)
    {   // best stamp value coverage, max stamp cnt in best, max stamp value in best
        int best = 0, best_cnt = INF;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> a[0];
            for (int j = 1; j <= a[0]; j++)
                cin >> a[j];
            memset(d, INF, sizeof(d));
            d[0] = 0;
            int curr = 0;
            for (int j = 1; j <= s*a[a[0]]+1; j++)
            {
                for (int k = 1; k <= a[0] && j >= a[k]; k++)
                    d[j] = min(d[j], d[j-a[k]]+1);
                if (d[j] > s)
                {   curr = j-1; break; }
            }
            if (curr > best)
                best = curr, best_cnt = a[0], memcpy(ans, a, sizeof(a));
            else if (curr == best)
            {
                if (a[0] < best_cnt)
                    best_cnt = a[0], memcpy(ans, a, sizeof(a));
                else if (a[0] == best_cnt)
                {
                    bool ok = false;
                    for (int k = a[0]; k > 0; k--)
                        if (a[k] != ans[k])
                        {   ok = a[k] < ans[k]; break; }
                    if (ok)
                        best_cnt = a[0], memcpy(ans, a, sizeof(a));
                }
            }
        }
        printf("max coverage =%4d :", best);
        for (int i = 1; i <= best_cnt; i++) printf("%3d", ans[i]);
        cout << endl;
    }
    return 0;
}
