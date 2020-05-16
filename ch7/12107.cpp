// UVa 12107 Digit Puzzle
// wangqc
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

const string chars = "*0123456789";
string s;
int maxd, n, solcnt, sp0, sp1;      // 1st space and 2nd space

int s2i(string num)
{
    int x = 0;
    for (char c : num)
        x = x * 10 + c - '0';
    return x;
}

int is_lead(int cur) { return cur == 0 || cur == sp0+1 || cur == sp1+1; }

bool valid()
{
    int x = s2i(s.substr(0, sp0));
    int y = s2i(s.substr(sp0+1, sp1-sp0-1));
    char z[5];
    sprintf(z, "%d", x * y);
    int lz = strlen(z), lo = sp1+1;
    if (n - lo != lz) return false;
    for (int i = lo; i < n; i++)
    {
        if (s[i] == '*') continue;
        if (s[i] != z[i-lo]) return false;
    }
    return true;
}

void check(int cur)
{
    if (solcnt > 1) return;
    if (cur == sp1)
    {   solcnt += valid(); return; }
    if (s[cur] != '*') 
        check(cur+1);
    else for (int i = 1; i < 11; i++)
    {
        if (chars[i] == '0' && is_lead(cur)) continue;
        s[cur] = chars[i];
        check(cur+1);
        s[cur] = '*';
    }
}

bool dfs(int d, int cur)
{
    if (d == maxd)
    {
        string t = s;
        solcnt = 0;
        check(0);
        s = t;
        return solcnt == 1;
    }
    if (cur == n) return false;
    if (cur == sp0 || cur == sp1) return dfs(d, cur+1);
    else for (char c : chars)
    {
        char t = s[cur];
        if (c == '0' && is_lead(cur)) continue;
        if (t != c)
        {
            s[cur] = c;
            if (dfs(d+1, cur+1)) return true;
            s[cur] = t;
        }
        else if (dfs(d, cur+1)) return true;
    }
    return false;
}

int main()
{
    int kase = 0;
    while (getline(cin, s) && s[0] != '0')
    {
        maxd = 0, n = s.size();
        sp0 = s.find(' ');
        sp1 = s.find(' ', sp0 + 1);
        while (!dfs(0, 0)) maxd++;
        cout << "Case " << ++kase << ": " << s << endl;
    }
    return 0;
}
