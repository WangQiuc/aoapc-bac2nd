// UVa12504 Updating a Dictionary
// wangqc

#include <iostream>
#include <string>
#include <map>

using namespace std;

string buf[105];

void print(char c, int n)
{
    cout << c ;
    for (int i = 0; i < n-1; i++)
        cout << buf[i] << ",";
    cout << buf[n-1] << endl;
}

int main()
{
    int T, kase = 0, i1, i2, i3;
    string s;
    map<string, string> dict[2];
    cin >> T;
    while (T--)
    {
        for (int i = 0; i < 2; i++)
        {
            dict[i].clear();
            cin >> s;
            int j = 0, n = s.size();
            if (n < 3) continue;
            while (j < n - 1)
            {
                string k, v;
                while (s[++j] != ':') k += s[j];
                while (s[++j] != ',' && s[j] != '}') v += s[j];
                dict[i][k] = v;
            }
        }
        i1 = i2 = i3 = 0;
        for (auto p : dict[1])
            if (!dict[0].count(p.first)) buf[i1++] = p.first;
        if (i1) print('+', i1);
        for (auto p : dict[0])
            if (!dict[1].count(p.first)) buf[i2++] = p.first;
        if (i2) print('-', i2);
        for (auto p : dict[1])
            if (dict[0].count(p.first) && dict[0][p.first] != p.second) buf[i3++] = p.first;
        if (i3) print('*', i3);
        if (!(i1 || i2 || i3)) cout << "No changes" << endl;
        cout << endl;
    }
    return 0;
}
