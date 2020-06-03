// UVa 12559 Finding Black Circles
// wangqc
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
const double PI = acos(-1);

struct Node
{
    int x, y, r;
    Node(int r=0, int x=0, int y=0): r(r), x(x), y(y) {}
    bool operator <(const Node &rhs) const
    {
        if (r == rhs.r)
            return x < rhs.x || (x == rhs.x && y < rhs.y);
        return r < rhs.r;
    }
};
int mp[105][105];

int main()
{
    int w, h, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        vector<Node> a;
        cin >> w >> h;
        char c;
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
            {
                cin >> c;
                mp[i][j] = c - '0';
            }
        for (int r = 5; r <= 50; r++)
            for (int x = r; x <= w - r; x++)
                for (int y = r; y <= h - r; y++)
                {
                    int k1 = 0, k2 = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        double angle = rand() / (RAND_MAX + 1.0) * 2 * PI;
                        int dx = int(x + r * cos(angle) + 0.5);
                        int dy = int(y + r * sin(angle) + 0.5); 
                        k1 += (dx >= 0 && dx <= w - 1 && dy >= 0 && dy <= h - 1 && mp[dy][dx]);
                        k2++;
                        if (k2 > 10 && 2 * k1 < k2) break;
                    }
                    if (k1 / (double)k2 > 0.8)
                        a.push_back(Node(r, x, y));
        }
        cout << "Case " << kase << ": " << a.size();
        for (auto node : a) 
            cout << " (" << node.r << "," << node.x << "," << node.y << ")";
        cout << endl;
    }
    return 0;
}