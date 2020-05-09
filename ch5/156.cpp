// UVa156 Ananagrams
// wangqc

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> ctr;
vector<string> words;

string repr(const string &s)
{
    string ans = s;
    for (int i = 0; i < ans.length(); i++)
        ans[i] = tolower(ans[i]);
    sort(ans.begin(), ans.end());
    return ans;
}

int main()
{
    int n = 0;
    string s;
    while (cin >> s && s[0] != '#')
    {
        words.push_back(s);
        ctr[repr(s)]++;
    }
    vector<string> ana;
    for (int i = 0; i < words.size(); i++)
        if ((ctr[repr(words[i])]) == 1) ana.push_back(words[i]);
    sort(ana.begin(), ana.end());
    for (int i = 0; i < ana.size(); i++)
        cout << ana[i] << endl;
    return 0;
}
