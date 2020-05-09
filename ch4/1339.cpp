// UVa1339 Ancient Cipher
// wangqc

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    char s1[105], s2[105];
    while (scanf("%s%s", s1, s2) == 2)
    {
        int n = strlen(s1), ok = 1;
        int ctr1[26] = {0}, ctr2[26] = {0};
        for (int i = 0; i < n; i++) ++ctr1[s1[i] - 'A'];
        for (int i = 0; i < n; i++) ++ctr2[s2[i] - 'A'];
        sort(ctr1, ctr1 + 26);
        sort(ctr2, ctr2 + 26);
        for (int i = 0; ok && i < 26; i++)
            if (ctr1[i] != ctr2[i]) ok = 0;
        printf(ok ? "YES\n" : "NO\n");
    }
    return 0;
}
