// UVa511 Do You Know The Way to San Jose?
// wangqc

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

typedef pair<double, double> PDD;
const double ESP = 1e-8;
const char* msg[] = 
{" using ", " no map at that detail level; using ", " no map contains that location\n", " unknown location\n"};

double dist(PDD x, PDD y)
{
    return (x.first-y.first)*(x.first-y.first) - (x.second-y.second)*(x.second-y.second);
}

struct Map
{
    double L, R, D, U, area, ratio;
    PDD center;
    string name;
    Map() {}
    Map(string s)
    {
        stringstream ss(s);
        double x1, x2, y1, y2;
        ss >> name >> x1 >> y1 >> x2 >> y2;
        if (x1 < x2) L = x1, R = x2;
        else L = x2, R = x1;
        if (y1 < y2) D = y1, U = y2;
        else D = y2, U = y1;
        center = make_pair((L + R) / 2, (D + U) / 2);
        area = (R - L) * (U - D);
        ratio = fabs((R - L) / (U - D) - 0.75);
    }
    bool cover(PDD x)
    {
        return x.first >= L && x.first <= R && x.second >= D && x.second <= U;
    }

    bool operator < (const Map &rhs)
    {
        return area < rhs.area;
    }
};

vector<Map> maps;
map<string, PDD> loc;
string target;

// detailed level (-area) > d > |ratio - 0.75| > d to right lower > x-coordinate
struct cmp 
{
    bool operator() (const Map &lhs, const Map &rhs) const
    {
        PDD x = loc[target];
        if (lhs.area - rhs.area < ESP)
        {
            double a = dist(x, lhs.center), b = dist(x, rhs.center);
            if (a - b < ESP)
                if (lhs.ratio - rhs.ratio < ESP)
                {
                    a = dist(x, make_pair(lhs.R, lhs.D));
                    b = dist(x, make_pair(rhs.R, rhs.D));
                    if (a - b < ESP) return lhs.L < rhs.L;
                    return a > b;
                }
                return lhs.ratio < rhs.ratio;
            return a < b;
        }
        return lhs.area > rhs.area;
    }
};

int main()
{
    string s;
    getline(cin, s);
    while (getline(cin, s) && s != "LOCATIONS")
        maps.push_back(Map(s));
    while (getline(cin, s) && s != "REQUESTS")
    {
        stringstream ss(s);
        double x, y;
        ss >> s >> x >> y;
        loc[s] = make_pair(x, y);
    }
    while (getline(cin, s) && s != "END")
    {
        stringstream ss(s);
        int level;
        ss >> target >> level;
        cout << target << " at detail level " << level;
        if (loc.count(target))
        {
            set<Map, cmp> cand;
            for (auto m : maps)
                if (m.cover(loc[target])) cand.insert(m);
            if (cand.size())
            {
                double t = 0;       // used for same-level grouping
                for (auto m : cand)
                    if (m.area != t)
                    {
                        t = m.area;
                        if (!--level) { cout << msg[0] << m.name << endl; break; }
                    }
                if (level) cout << msg[1] << cand.rbegin()->name << endl;
            }
            else cout << msg[2];
        }
        else cout << msg[3];

        
    }
    return 0;
}
