// UVa 11059 Maximum Product
// wangqc
#include<iostream>

using namespace std;

int main()
{
    
    int S[20], n, kase = 0;
    while (cin >> n && n)
    {
        long long product = 0;
        for (int i  = 0; i < n; i++)
            cin >> S[i];
        for (int i = 0; i < n; i++)
        {
            long long v = 1;
            for (int j = i; j < n; j++)
            {
                v *= S[j];
                if (v > product) product = v;
            }
        }
        cout << "Case #" << ++kase << ": The maximum product is " << product << ".\n\n";
    }
    return 0;
}
