// UVa506 System Dependencies
// wangqc

#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

const int maxn = 10000;

int cnt = 0;
map<string, int> idx;
string name[maxn];

vector<int> src[maxn], dst[maxn];
int status[maxn]; // 0-not installed, 1-explicitly installed, 2-implicitly installed
vector<int> installed;

int ID(const string &item)
{
    if (!idx.count(item))
    {
        name[++cnt] = item;
        idx[item] = cnt;
    }
    return idx[item];
}

bool required(int item)
{
    for (auto x : dst[item])
        if (status[x]) return true;
    return false;
}

void install (int item, bool expl)
{
    if (!status[item])
    {
        for (int s : src[item])
            install(s, false);
        cout << "   Installing " << name[item] << endl;
        status[item] = expl ? 1 : 2;
        installed.push_back(item);
    }
}

void remove(int item, bool expl)
{
    if ((expl || status[item] == 2) && !required(item))
    {
        status[item] = 0;
        installed.erase(remove(installed.begin(), installed.end(), item), installed.end());
        cout << "   Removing " << name[item] << endl;
        for (int s : src[item])
            remove(s, false);
    }
}

void list()
{
    for (int i : installed)
        cout << "   " << name[i] << endl;
}

int main()
{
    string line, cmd;
    memset(status, 0, sizeof(status));
    while (getline(cin, line))
    {
        cout << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if (cmd[0] == 'E') break;   // END
        if (cmd[0] == 'L') list();  // List
        else
        {
            string s;
            ss >> s;
            int x = ID(s);
            if (cmd[0] == 'D')      // Depend
            {
                string d;
                while (ss >> d)
                {
                    int y = ID(d);
                    src[x].push_back(y);
                    dst[y].push_back(x);
                }
            }
            else if (cmd[0] == 'I') // Install
            {
                if (status[x]) cout << "   " << s << " is already installed.\n";
                else install(x, true);
            }
            else                    // Remove
            {
                if (!status[x]) cout << "   " << s << " is not installed.\n";
                else if (required(x)) cout << "   " << s << " is still needed.\n";
                else remove(x, true);
            }  
        } 
    }
    return 0;
}
