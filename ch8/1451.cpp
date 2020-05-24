// UVa 1451 Averaga
// wangqc
#include<iostream>

using namespace std;

const int maxn = 100005;
int n, L, sum[maxn], p[maxn]; // avg((i,j]) = (sum[j]-sum[i]) / (j-i)
char s[maxn];

int compare_avg(int x1, int x2, int x3, int x4)
{
    return (sum[x2]-sum[x1])*(x4-x3) - (sum[x4]-sum[x3])*(x2-x1);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> L >> s;
        sum[0] = 0;
        for (int i = 0; i < n; i++) sum[i+1] = sum[i]+s[i]-'0';
        int subL = 0, subR = L;     // best interval [subL+1, subR] or (subL, subR]
        int i = 0, j = 0;
        for (int x = L; x <= n; x++)
        {
            while (j-i > 1 && compare_avg(p[j-2], x-L, p[j-1], x-L) >= 0)
                j--;    // remove concave point
            p[j++] = x-L;
            while (j-i > 1 && compare_avg(p[i], x, p[i+1], x) <= 0)
                i++;    // find tangent at i
            int t = compare_avg(p[i], x, subL, subR);
            if (t > 0 || (t == 0 && x - p[i] < subR - subL))
                subL = p[i], subR = x;
        }
        cout << subL + 1 << " " << subR << endl;   
    }
    return 0;
}
