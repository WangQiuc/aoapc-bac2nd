// UVa673 Parentheses Balance
// wangqc

#include<iostream>
#include<cstring>
#include<stack>

using namespace std;

const char *pt = "([)]";    // pattern

bool match()
{
    stack<char> st;
    string s;
    getline(cin, s);
    for (auto c : s)
    {
        int i = strchr(pt, c) - pt;
        if (i < 2) st.push(c);
        else if (!st.empty() && pt[i-2] == st.top()) st.pop();
        else return false;
    }
    return st.empty();
}

int main()
{
    int T;
    cin >> T; getchar();
    while (T--)
        cout << (match() ? "Yes" : "No") << endl;
    return 0;
}
