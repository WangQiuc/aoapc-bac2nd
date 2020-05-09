// UVa10763 Foreign Exchange
// wangqc

#include <iostream>
#include <map>

using namespace std;

map<pair<int, int>, int> db;

int main()
{
    int n, x, y;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            if (x > y) db[make_pair(x, y)]++;
            else db[make_pair(y, x)]--;
        }
        bool ok = true;
        for (map<pair<int, int>, int>::iterator i = db.begin(); ok && i != db.end(); ++i)
            if (i->second) ok = false;
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}
