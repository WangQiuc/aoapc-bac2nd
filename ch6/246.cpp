// UVa246 10-20-30
// wangqc

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <set>

using namespace std;

const char *msg[3] = {"Draw: ", "Loss: ", "Win : "};
const int maxn = 8;
int n, cnt;
int idx[maxn-1];
vector<deque<int> > p(maxn);
deque<int> &deck = p[0];

bool remove(int &i)     // true if all piles are clear
{
    n--;
    for (int j = i--; j < n; j++) idx[j] = idx[j+1];
    return n == 0;
}

bool pick(deque<int> &x) 
{ 
    int m = x.size();
    if (m < 3) return false;
    if ((x[0] + x[1] + x[m-1]) % 10 == 0)
    {
        deck.push_back(x[0]); deck.push_back(x[1]); deck.push_back(x[m-1]);
        x.pop_front(); x.pop_front(); x.pop_back(); 
        return true;
    }
    if ((x[0] + x[m-2] + x[m-1]) % 10 == 0)
    {
        deck.push_back(x[0]); deck.push_back(x[m-2]); deck.push_back(x[m-1]);
        x.pop_front(); x.pop_back(); x.pop_back(); 
        return true;
    }
    if ((x[m-3] + x[m-2] + x[m-1]) % 10 == 0)
    {
        deck.push_back(x[m-3]); deck.push_back(x[m-2]); deck.push_back(x[m-1]);
        x.pop_back(); x.pop_back(); x.pop_back(); 
        return true;
    }
    return false;
}

bool init()
{
    n = maxn - 1, cnt = 14;
    int card;
    if (cin >> card && !card) return false;
    deck.clear();
    for (int i = 0; i < n; i++) { idx[i] = i + 1; p[i+1].clear(); }
    // first two rounds
    for (int i = 1; i <= n; i++) { p[i].push_back(card); cin >> card; }
    for (int i = 1; i <= n; i++) { p[i].push_back(card); cin >> card; }
    deck.push_back(card);
    for (int i = cnt; i < 51; i++) { cin >> card; deck.push_back(card); }
    return true;
}

int exec()
{
    set<vector<deque<int> > > vis;
    for (int i = 0; !deck.empty(); i = (i+1) % n)
    {
        if (vis.count(p)) return 0;
        vis.insert(p);
        p[idx[i]].push_back(deck.front()); deck.pop_front(); cnt++;
        while(pick(p[idx[i]]));
        if (p[idx[i]].empty() && remove(i)) return 2;
    }
    return 1;
}

int main()
{
    while (init())
        cout << msg[exec()] << cnt << endl;
    return 0;
}
