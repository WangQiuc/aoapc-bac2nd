// UVa 11925 Generating Permutations
// wangqc
#include<iostream>
#include<vector>

using namespace std;

const int maxn = 1000;
int n;
vector<int> a, op;

bool valid()
{
    for (int i = 0; i < n; i++)
        if (a[i] != i+1) return false;
    return true;
}

int main()
{
    while (cin >> n && n)
    {
        a.resize(n); 
        op.clear();
        for (int i = 0; i < n; i++) cin >> a[i];
        while (!valid())
        {
            if (a[0] > a[1] && a[0] != n)
            {
                op.push_back(1);
                swap(a[0], a[1]);
            }
            else
            {
                op.push_back(2);
                a.insert(a.begin(), a[n-1]);
                a.erase(a.end() - 1);
            }  
        }
        for (int i = op.size()-1; i >= 0; i--) cout << op[i];
        cout << endl;
    }
    return 0;
}
