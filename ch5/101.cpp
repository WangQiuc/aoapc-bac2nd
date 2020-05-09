// UVa101 The Blocks Problem
// wangqc

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

void find_block(int x, int& p, int& i)
{
    for (p = 0; p < n; p++)
        for (i = 0; i < pile[p].size(); i++)
            if (pile[p][i] == x) return;
}

void return_blocks(int p, int i)
{
    for (int j = i+1; j < pile[p].size(); j++)
    {
        int b = pile[p][j];
        pile[b].push_back(b);
    }
    pile[p].resize(i + 1);
}

void pile_onto(int p1, int i, int p2)
{
    for (int j = i; j < pile[p1].size(); j++)
        pile[p2].push_back(pile[p1][j]);
    pile[p1].resize(i);
}

void print()
{
    for (int p = 0; p < n; p++)
    {
        printf("%d:", p);
        for (int i = 0; i < pile[p].size(); i++)
            printf(" %d", pile[p][i]);
        printf("\n");
    }
}

int main()
{
    int a, b;
    cin >> n;
    string verb, prep;
    for (int p = 0; p < n; p++)
        pile[p].push_back(p);
    while (cin >> verb >> a >> prep >> b)
    {
        int pa, pb, ia, ib;
        find_block(a, pa, ia);
        find_block(b, pb, ib);
        if (pa == pb) continue;
        if (verb == "move") return_blocks(pa, ia);
        if (prep == "onto") return_blocks(pb, ib);
        pile_onto(pa, ia, pb);
    }
    print();
    return 0;
}
