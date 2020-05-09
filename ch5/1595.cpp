// UVa1595 Symmetry
// wangqc

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool check(map<int, vector<int> > points)
{
    int m, init = 0;
    for (auto point : points)
    {
        sort(point.second.begin(), point.second.end());
        int i = 0, j = point.second.size() - 1;
        if (!init) m = point.second[i] + point.second[j], init = 1;
        while (i <= j)
            if (point.second[i++] + point.second[j--] != m)
                return false;
    }
    return true;
}

int main()
{
    int x, y, n, T;
    cin >> T;
    while (T--)
    {
        map<int, vector<int> > points; 
        cin >> n;
        while (n--)
        {
            cin >> x >> y;
            points[y].push_back(x);
        }
        cout << (check(points) ? "YES" : "NO") << endl;
    }
    return 0;
}
