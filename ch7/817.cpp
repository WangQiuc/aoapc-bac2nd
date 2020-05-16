// UVa 817 According to Bartjens
// wangqc
#include<iostream>
#include<cstring>
#include<string>
#include<vector>

using namespace std;
const string sym = " *+-";
int n;
string s, addin;
vector<int> nums;
vector<char> ops;

bool calculate()
{   // sz of nums, sz-1 of ops
    int sz = nums.size();
    for (int i = 0; i < sz - 1; i++)    // process '*' first
        if (ops[i] == '*')
            nums[i+1] = nums[i]*nums[i+1], nums[i] = -1, ops[i] = ' ';
    vector<int> nums2;    // remove all -1  (mulitply result stored in nums[i+1])
    vector<char> ops2;    // remove all ' ' (previous '*')
    for (int i = 0; i < sz; i++)
    {
        if (i && ops[i-1] != ' ') ops2.push_back(ops[i-1]);
        if (nums[i] != -1)  nums2.push_back(nums[i]);
    }
    sz = nums2.size();
    int x = nums2[0];
    for (int i = 1; i < sz; i++)
    {
        ops2[i-1] == '+' ? x += nums2[i] : x -= nums2[i];
    }
    return x == 2000;
}

bool check()
{
    nums.clear(); ops.clear();
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        x = x * 10 + s[i] - '0';
        if (addin[i] != ' ')        // there is an op
        {
            nums.push_back(x);
            x = 0;
            ops.push_back(addin[i]);
        }
    }
    int sz = nums.size(); // check leading 0 issue, ∑|nums| should equals to n
    for (int x : nums)
        while (x /= 10) sz++;
    return sz == n && calculate();
}

void print()
{
    cout << "  ";
    for (int i = 0; i < n; i++)
    {
        cout << s[i];
        if (i != n-1 && addin[i] != ' ') cout << addin[i];
    }
    cout << "=" << endl;
}

bool dfs(int i)
{
    if (i == n-1)
    {
        if (check()) {print(); return true;}
        return false;
    }
    bool ok = false;
    for (char c : sym)
    {
        addin[i] = c;
        ok |= dfs(i+1);
    }
    return ok;   
}

int main()
{
    int kase = 0;
    while (cin >> s && s != "=")
    {
        cout << "Problem " << ++kase << endl;
        if (s == "2000=") cout << "  IMPOSSIBLE" << endl;
        else
        {
            n = s.length() - 1;
            ops.resize(10);
            if (!dfs(0)) cout << "  IMPOSSIBLE" << endl;
        }
    }
    return 0;
}
