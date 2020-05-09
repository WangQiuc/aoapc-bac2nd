// UVa548 Tree
// wangqc

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const int maxv = 10010;
int inorder[maxv], postorder[maxv], lb[maxv], rb[maxv];
int n, best_leaf, best_sum;

bool read_list(int *order)
{
    string line;
    if (!getline(cin, line)) return false;
    stringstream ss(line);
    n = 0;
    int x;
    while (ss >> x) order[n++] = x;
    return n > 0;
}

int build(int l1, int r1, int l2, int r2)
{
    if (l1 > r1) return 0;
    int root = postorder[r2];
    int p = l1;
    while (inorder[p] != root) p++;
    int lcnt = p - l1;
    lb[root] = build(l1, p-1, l2, l2+lcnt-1);
    rb[root] = build(p+1, r1, l2+lcnt, r2-1);
    return root;
}

void dfs(int x, int sum)
{
    sum += x;
    if (!lb[x] && !rb[x])
        if (sum < best_sum || (sum == best_sum && x < best_leaf))
            best_leaf = x, best_sum = sum;
    if (lb[x]) dfs(lb[x], sum);
    if (rb[x]) dfs(rb[x], sum);
}

int main()
{
    while(read_list(inorder))
    {
        read_list(postorder);
        build(0, n-1, 0, n-1);
        best_sum = 1e9;
        dfs(postorder[n-1], 0);
        cout << best_leaf << endl;
    }
    return 0;
}
