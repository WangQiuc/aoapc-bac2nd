// UVa 1605 Building for UN
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

char country(int x)
{
    if (x < 26) return 'A' + x;
    return 'a' + x - 26;
}

int main()
{
    int n;
    while (cin >> n)
    {
        cout << 2 << " " << n << " " << n << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cout << country(i);
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) cout << country(j);
            cout << endl;
        }
    }
    return 0;
}
