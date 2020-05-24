// UVa 11572 Unique Snowflakes
// wangqc
#include<iostream>
#include<unordered_map>

using namespace std;

unordered_map<int, int> idx;

int main()
{
    int x, n, T;
    cin >> T;
    while (T--)
    {
        idx.clear();
        int maxlen = 0, i = -1;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            cin >> x;
            if (idx.count(x)) i = max(i, idx[x]);
            idx[x] = j;
            maxlen = max(maxlen, j - i);
        }
        cout << maxlen << endl;
    }
    return 0;
}
