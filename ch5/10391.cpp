// UVa10391 Compound Words
// wangqc

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<string> words;
set<string> valid;

int main()
{
    int i = 0;
    string word;
    while (cin >> word)
    {
        words.push_back(word);
        valid.insert(word);
    }
    for (auto word : words)
    {
        bool ok = false;
        for (int j = 1; !ok && j < word.length(); j++)
            ok = valid.count(word.substr(0, j)) && valid.count(word.substr(j));
        if (ok) cout << word << endl;
    }
    return 0;
}
