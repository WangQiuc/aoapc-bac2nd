// UVa 12627 Erratic Expansion
// wangqc
#include<iostream>

using namespace std;

long long c(int k) { return k ? 3 * c(k-1) : 1; }

long long f(int k, int i)   // number of red ballons at k at matrix[:i];
{
    if (!i) return 0;
    if (!k) return 1;
    if (i < 1<<(k-1)) return 2 * f(k-1, i);
    return 2 * c(k-1) + f(k-1, i - (1<<(k-1)));
}

int main()
{
    int k, a, b, T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++)
    {
        cin >> k >> a >> b;
        cout << "Case " << kase << ": " << f(k, b) - f(k, a-1) << endl;
    }
    return 0;
}
