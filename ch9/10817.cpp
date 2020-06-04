// UVa 10817 Headmaster's Headache
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>

using namespace std;

const int maxn = 125;
const int maxs = 1 << 8;
const int INF = 0x3fffffff;
int m, n, s, cost[maxn], st[maxn], memo[maxn][maxs][maxs];

// s1-lessons only 1 teacher can teach, s2-lessons at least 2 teachers can teach
int dfs(int i, int s1, int s2)
{
    if (i == m+n) 
        return s2 == (1 << s) - 1 ? 0 : INF;
    int &ans = memo[i][s1][s2];
    if (ans >= 0) return ans;
    ans = cost[i] + dfs(i+1, s1^st[i], s2|(s1&st[i]));  // hire i
    if (i >= m) ans = min(ans, dfs(i+1, s1, s2));       // min(hire, not hire)
    return ans;    
}

int main()
{
    int x;
    string line;
    while (cin >> s >> m >> n && s)
    {
        getchar();
        for (int i = 0; i < m+n; i++)
        {
            getline(cin, line);
            stringstream ss(line);
            ss >> cost[i];
            st[i] = 0;
            while (ss >> x) st[i] |= (1 << (x-1));
        }
        memset(memo, -1, sizeof(memo));
        cout << dfs(0, 0, 0) << endl;
    }
    return 0;
}
