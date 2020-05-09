// UVa1597 Searching the Web
// wangqc

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int maxn = 105;
const string split[3] = {"**********", "----------", "=========="};

int n;      // number of documents
map<string, set<int> > idx[maxn];
vector<string> db[maxn];

void exec(string w1, string w2, int cmd)        // A AND B, A OR B
{
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        bool b1 = idx[i].count(w1), b2 = idx[i].count(w2);
        if ((cmd && (b1 || b2)) || (!cmd && (b1 && b2)))
        {
            if (found++) cout << split[1] << endl;
            set<int> match;
            if (b1) for (auto j : idx[i][w1]) match.insert(j);
            if (b2) for (auto j : idx[i][w2]) match.insert(j);
            for (auto j : match) cout << db[i][j] << endl;
        }
    }
    if (!found) cout << "Sorry, I found nothing." << endl;
}

void exec(string w, int cmd)                    // NOT A, A
{
    int found = 0;
    for (int i = 0; i < n; i++)
        if ((cmd && idx[i].count(w)) || (!cmd && !idx[i].count(w)))
        {
            if (found++) cout << split[1] << endl;
            if (cmd) for (auto j : idx[i][w]) cout << db[i][j] << endl;
            else for (auto s : db[i]) cout << s << endl;
        }
    if (!found) cout << "Sorry, I found nothing." << endl;
}

int main()
{
    int m, i;
    string s, word, word2;
    scanf("%d\n", &n);
    for (i = 0; i < n; i++)
        for (int j = 0; getline(cin, s) && s != split[0]; j++)
        {
            db[i].push_back(s);
            for (int k = 0; k < s.size(); k++)
                s[k] = isalpha(s[k]) ? tolower(s[k]) : ' ';
            stringstream ss(s);
            while (ss >> word) idx[i][word].insert(j);
        }
    scanf("%d\n", &m);
    while (m--)
    {
        getline(cin, s);
        if ((i=s.find("AND")) != -1)     exec(s.substr(0, i-1), s.substr(i+4), 0);
        else if ((i=s.find("OR")) != -1) exec(s.substr(0, i-1), s.substr(i+3), 1);
        else if (s.find("NOT") != -1)    exec(s.substr(4), 0);
        else                             exec(s, 1);
        cout << split[2] << endl;
    }
    return 0;
}
