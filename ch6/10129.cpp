// UVa10129 Play On Words
// wangqc

#include <iostream>
#include <cstring>

using namespace std;

int p[26], v[26], deg[26];
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x; }
int c2i(char c) { return c - 'a'; }

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        string word;
        memset(v, 0, sizeof(v));
        memset(deg, 0, sizeof(deg));
        for (int i = 0; i < 26; i++) p[i] = i;
        int cc = 26;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            int x1 = c2i(word[0]), x2 = c2i(word[word.length()-1]);
            v[x1] = v[x2] = 1;
            deg[x1]++, deg[x2]--;
            int p1 = find(x1), p2 = find(x2);
            if (p1 != p2)
                p[p1] = p2, cc--;
        }
        int d = 0;
        bool ok = true;
        for (int i = 0; ok && i < 26; i++)
        {
            if (!v[i]) cc--;
            else if (deg[i]) 
            {
                if (d < 2 && (deg[i] == 1 || deg[i] == -1)) d++;
                else ok = false;
            }
        }
        if (ok && cc == 1) cout << "Ordering is possible." << endl;
        else cout << "The door cannot be opened." << endl;
    }
    return 0;
}
