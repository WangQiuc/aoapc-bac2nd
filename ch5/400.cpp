// UVa400 Unix ls
// wangqc

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int maxcol = 60;
string filenames[105];

void print(const string &s, int len, char padding)
{
    cout << s;
    for (int i = 0; i < len - s.length(); i++)
        cout << padding;
}

int main()
{
    int n;
    while (cin >> n)
    {
        int M = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> filenames[i];
            M = max(M, (int)filenames[i].length());
        }
        int col = (maxcol - M) / (M + 2) + 1, row = (n - 1) / col + 1;
        print("", maxcol, '-');
        cout << endl;
        sort(filenames, filenames + n);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                int idx = i + j * row;
                if (idx < n) print(filenames[idx], idx + row < n ? M + 2 : M, ' ');
            }
            cout << endl;
        }
    }
    return 0;
}
