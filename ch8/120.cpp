// UVa 120 Stacks of Flapjacks
// wangqc
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

int n, a[32];

void flip(int p)
{
    for (int i = 0; i < p-i; i++)
        swap(a[i], a[p-i]);
    cout << n-p << " ";
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        stringstream ss(s);
        cout << s << endl;
        n = 0;
        while (ss >> a[n]) n++;
        for (int i = n-1; i >= 0; i--)
        {
            int p = max_element(a, a+i+1) - a;
            if (p == i) continue;  // already at the right place
            if (p) flip(p);        // no need to flip if p == 0, flip(0) no flip
            flip(i);
        }
        cout << "0\n";
    }
    return 0;
}
