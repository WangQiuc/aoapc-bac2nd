// UVa514 Rails
// wangqc

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int maxn = 1010;
int n, target[maxn];

int main()
{
    while (cin >> n && n)
    {
        while (cin >> target[1] && target[1])
        {
            stack<int> s;
            int A = 1, B = 1;
            for (int i = 2; i <= n; i++)
                cin >> target[i];
            bool ok = true;
            while (ok && B <= n)
            {
                if (A == target[B]) A++, B++;
                else if (!s.empty() && s.top() == target[B]) s.pop(), B++;
                else if (A <= n) s.push(A++);
                else ok = false;
            }
            cout << (ok ? "Yes" : "No") << endl;
        }
        cout << endl;
    }
    return 0;
}
