// UVa508 Morse Mismatch
// wangqc

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

string s, cache[105];
map<char, string> morse;
map<string, string> codex;

int main()
{
    char c;
    int idx = 0;
    while (cin >> c && c != '*')       // morse table
    {
        cin >> s;
        morse[c] = s;
    }
    while (cin >> s && s != "*")       // strings' morse
    {  
        cache[++idx] = s;
        string code = "";
        for (int i = 0; i < s.size(); i++)
            code += morse[s[i]];
        codex[s] = code;
    }
    while (cin >> s && s != "*")       // decode
    {
        int n = s.size(), found = 0, cid = 0, gap = 80;
        for (int i = 1; i <= idx; i++)
        {
            string cand = codex[cache[i]];
            if (cand == s)
            {
                if (!found) cout << cache[i], found = 1;
                else {cout << '!'; break;}
            }
            else
            {
                int m = cand.size(), prefix = 1;
                if (m != n && abs(m - n) < gap)
                {
                    for (int j = 0; prefix && j < min(m, n); j++)
                        if (cand[j] != s[j]) prefix = 0;
                    if (prefix) cid = i, gap = abs(m - n);
                }
            }
        }
        if (!found) cout << cache[cid] << '?';
        cout << endl;
    }
    return 0;
}
