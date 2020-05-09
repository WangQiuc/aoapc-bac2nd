// UVa442 Matrix Chain Multiplication
// wangqc

#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Matrix
{
    int a, b;
    Matrix(int a = 0, int b = 0): a(a), b(b) {}
} m[26];

stack<Matrix> s;

int c2i(char c)
{
    return c - 'A';
}

int main()
{
    int n;
    string var, expr;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> var;
        cin >> m[c2i(var[0])].a >> m[c2i(var[0])].b;
    }
    while (cin >> expr)
    {
        int len = expr.length();
        bool ok = true;
        int ans = 0;
        for (int i = 0; i < len; i++)
        {
            if (isalpha(expr[i])) s.push(m[c2i(expr[i])]);
            else if (expr[i] == ')')
            {
                Matrix m2 = s.top(); s.pop();
                Matrix m1 = s.top(); s.pop();
                if (m1.b != m2.a) { ok = false; break; }
                ans += m1.a * m1.b * m2.b;
                s.push(Matrix(m1.a, m2.b));
            }
        }
        ok ? cout << ans << endl : cout << "error" << endl;
    }
    return 0;
}
