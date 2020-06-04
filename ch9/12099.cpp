// UVa 12099 The Bookcase
// wangqc
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 75;
const int maxw = 30;
const int INF = 0x3fffffff;

struct Book
{
    int h, w;
    bool operator < (const Book &rhs) const { return h > rhs.h || (h == rhs.h && w > rhs.w); }
} books[maxn];

int dp[2][maxn*maxw][maxn*maxw], sumw[maxn];

inline int get_h(int w, int h) { return w ? 0 : h; }

inline void update(int &mind, int d) { if (mind < 0 || mind > d) mind = d; }


int main()
{
    int n, T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> books[i].h >> books[i].w;
        sort(books, books+n);
        sumw[0] = 0;
        for (int i = 0; i < n; i++)
            sumw[i+1] = sumw[i] + books[i].w;
        dp[0][0][0] = 0;
        int t = 0;
        for (int i = 0; i < n; i++)
        {   // replace memset
            for (int j = 0; j <= sumw[i+1]; j++)
                for (int k = 0; k <= sumw[i+1]-j; k++)
                    dp[t^1][j][k] = -1;
            for (int j = 0; j <= sumw[i]; j++)
                for (int k = 0; k <= sumw[i]-j; k++) if (dp[t][j][k] >= 0)
                {
                    update(dp[t^1][j][k], dp[t][j][k]); // 1st layer no change
                    update(dp[t^1][j+books[i].w][k], dp[t][j][k] + get_h(j,books[i].h)); // 2nd layer 
                    update(dp[t^1][j][k+books[i].w], dp[t][j][k] + get_h(k,books[i].h)); // 3rd layer
                }
            t ^= 1;
        }
        int ans = INF;
        for (int j = 1; j <= sumw[n]; j++)
            for (int k = 1; k <= sumw[n]-j; k++) if (dp[t][j][k] >= 0)
            {
                int w = max(max(j, k), sumw[n]-j-k);
                int h = books[0].h + dp[t][j][k];
                ans = min(ans, w*h);
                
            }
        cout << ans << endl;
    }
    return 0;
}
