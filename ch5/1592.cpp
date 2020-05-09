// UVa1592 Database
// wangqc

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int n, m;
string db[10005][12];

void check()
{
    for (int c1 = 0; c1 < m; c1++)
        for (int c2 = c1+1; c2 < m; c2++)
        {
            map<string, int> cache;
            for (int r = 0; r < n; r++)
            {
                string key = db[r][c1] + "," + db[r][c2];
                if (cache.count(key))
                {
                    printf("NO\n%d %d\n%d %d\n", cache[key]+1, r+1, c1+1, c2+1);
                    return;
                }
                else cache[key] = r;
            }
        }
    printf("YES\n");
}


int main()
{
    string s;
    while (getline(cin, s))
    {
        stringstream ss(s);
        if (!(ss >> n >> m)) break;
        for (int r = 0; r < n; r++)
        {
            getline(cin, s);
            int idx = 0;
            for (int c = 0; c < m; c++)
            {
                int p = s.find(',', idx);
                if (p == string::npos) p = s.length();
                db[r][c] = s.substr(idx, p - idx);
                idx = p + 1;
            }
        }
        check();
    }
    return 0;
}
