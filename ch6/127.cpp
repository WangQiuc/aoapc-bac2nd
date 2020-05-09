// UVa127 "Accordian" Patience
// wangqc

#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int maxn = 53;      // start node - 0, end node - 53
int pre[maxn + 1];        // double linked list
int nxt[maxn + 1];
stack<string> piles[maxn];

void remove(int i)
{
    nxt[pre[i]] = nxt[i];
    pre[nxt[i]] = pre[i];
}

bool match(int i, int j)
{
    string c1 = piles[i].top(), c2 = piles[j].top();
    return c1[0] == c2[0] || c1[1] == c2[1];
}

int find(int i)  // return the left idx for i to pile on, return 0 if not found
{
    if (!pre[i]) return 0;
    int k = 3, j = i;
    while (j && k--) j = pre[j];
    if (j && match(i, j)) return j;
    return match(i, pre[i]) ? pre[i] : 0;
}

bool init()
{
    string card;
    if (cin >> card && card[0] == '#') return false;
    for (int i = 0; i <= maxn - 1; i++) // never reach pre[0], next[maxn]
    {
        pre[i+1] = i;
        nxt[i] = i+1;
        stack<string>().swap(piles[i]);
    }
    piles[1].push(card);
    for (int i = 2; i <= 52; i++)
    {
        cin >> card;
        piles[i].push(card);
    }
    return true;
}

int main()
{
    while (init())
    {
        for (;;)
        {
            bool found = false;
            for (int i = nxt[0]; !found && i != maxn; i = nxt[i])
                while (int j = find(i))
                {
                    piles[j].push(piles[i].top()); 
                    piles[i].pop();
                    if (piles[i].empty()) remove(i);
                    found = true, i = j;
                }
            if (!found) break;
        }
        int cnt = 0;
        for (int i = nxt[0]; i != maxn; i = nxt[i]) cnt++;
        cout << cnt << " pile" << (cnt > 1 ? "s " : " ") << "remaining:";
        for (int i = nxt[0]; i != maxn; i = nxt[i])
            cout << " " << piles[i].size();
        cout << endl;
    }
    return 0;
}
