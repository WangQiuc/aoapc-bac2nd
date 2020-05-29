// UVa
// wangqc
#include<iostream>

using namespace std;

const int maxn = 100005;
char a[maxn];

int main()
{
    int n, d;
    while (cin >> n >> d && n)
    {
        getchar();                      // read '\n'
        int p = 0; d = n-d;             // keep d chars
        for (int i = n; i > 0; i--)     // i chars not read yet;
        {
            char c = getchar();
            while (p > 0 && p+i > d && a[p-1] < c) // have room to delete a char
                p--;
            if (p < d) a[p++] = c;
        }
        a[p] = '\0';
        cout << a << endl;
    }
    return 0;
}
