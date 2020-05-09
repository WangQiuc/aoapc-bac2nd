// UVa1593 Alignment of Code
// wangqc

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const int maxc = 185;
const int maxr = 1005;
int maxlen[maxc];
vector<string> code[maxr];

void print(const string &s, int len)
{
    cout << s;
    for (int i = s.length(); i <= len; i++)
        cout << " ";
}

int main()
{
    int n = 0;
    string s, buf;
    for (; getline(cin, s); n++)
    {
        stringstream ss(s);
        for (int j = 0; ss >> buf; j++)
        {
            code[n].push_back(buf);
            maxlen[j] = max(maxlen[j], (int) buf.length());
        }
    }
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        for (; j < code[i].size() - 1; j++)
            print(code[i][j], maxlen[j]);
        cout << code[i][j] << endl;
    }
    return 0;
}
