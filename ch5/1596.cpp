// UVa1596 Bug Hunt
// wangqc

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct var
{
    string name;
    int idx;

    bool operator < (const var &x) const
    {
        return name < x.name || (name == x.name && idx < x.idx);
    }
};

map<string, int> sizes;
map<var, int> vars;         // save space of unassigned index
int i;

// 3 parsing status
// 0: a[i]; declare, i can be any value
// 1: a[i] = j; assign, i < a.size()
// 2: x = a[i]; get_value, i has been assigned, vars.count(a[i])
bool parse(string s, var &x, int status)
{
    x.name = s.substr(0, (i = s.find("[")));
    s = s.substr(i + 1);
    s.pop_back();
    if (s.back() == ']')
    {
        var y;
        if (!parse(s, y, 2)) return false;
        x.idx = vars[y];
    }
    else x.idx = stoi(s);
    return !status || (status == 1 && x.idx < sizes[x.name]) || vars.count(x);
}

int main()
{
    string s;
    while (getline(cin, s) && s != ".")
    {
        sizes.clear();
        vars.clear();
        int bug = 0;
        do 
        {
            bug++;
            var x, y;
            if ((i = s.find("=")) == string::npos)
            {
                if (parse(s, x, 0)) sizes[x.name] = x.idx;
                else break;
            }
            else
            {
                string sx = s.substr(0, i);
                string sy = s.substr(i + 1);
                if (parse(sx, x, 1))
                {
                    if (isdigit(sy[0])) vars[x] = stoi(sy);
                    else if (parse(sy, y, 2)) vars[x] = vars[y];
                    else break;
                }
                else break;
            }
        } while (getline(cin, s) && s != ".");
        if (s != ".") while (getline(cin, s) && s != "."); 
        else bug = 0;
        cout << bug << endl;
    }
    return 0;
}
