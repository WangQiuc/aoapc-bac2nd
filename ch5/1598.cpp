// UVa1598 Exchange
// wangqc

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 0x7fffffff;
struct Order
{
    int id, q, p;
    bool in;                // in - buy order; !in - sell order
    Order() {}
    Order(int id, int q, int p, bool in) : id(id), q(q), p(p), in(in) {}
    bool operator<(const Order &rhs) const
    {
        return p < rhs.p || (p == rhs.p && id > rhs.id);
    }
    bool operator>(const Order &rhs) const
    {
        return p > rhs.p || (p == rhs.p && id > rhs.id);
    }
};

vector<Order> orders;
vector<bool> del;
priority_queue<Order> buy_q;
priority_queue<Order, vector<Order>, greater<Order> > sell_q;
map<int, int> buy_stock;    // key = price, value = qnt
map<int, int> sell_stock;

void init()
{
    buy_stock.clear();
    sell_stock.clear();
    vector<Order>().swap(orders);
    vector<bool>().swap(del);
    priority_queue<Order>().swap(buy_q);
    priority_queue<Order, vector<Order>, greater<Order> >().swap(sell_q);
    buy_q.push(Order(0,0,0,1));
    sell_q.push(Order(INF,0,99999,0));  // INF id ensures never be the top
    del.push_back(false);               // placeholder for idle index 0
    orders.push_back(Order());          // placeholder for idle index 0
}

bool lazy_del()
{
    while (del[buy_q.top().id]) buy_q.pop();
    while (sell_q.top().id != INF && del[sell_q.top().id]) sell_q.pop();
    return sell_q.size() > 1;  // never use absent placeholder sell(0,99999)
}

void exec(char cmd)
{
    if (cmd != 'C')
    {
        while (lazy_del() && buy_q.top().p >= sell_q.top().p)
        {
            Order &b = orders[buy_q.top().id], &s = orders[sell_q.top().id];
            buy_q.pop(), sell_q.pop();
            int q = min(b.q, s.q);
            b.q -= q, buy_stock[b.p] -= q, s.q -= q, sell_stock[s.p] -= q;
            if (b.q) buy_q.push(b);
            if (s.q) sell_q.push(s);
            cout << "TRADE " << q << " " << (cmd == 'B' ? s.p : b.p) << endl;
        }
    }
    else lazy_del();
}

int main()
{
    int n, cid, q, p, kase;
    string cmd;
    while (cin >> n)
    {
        init();
        if (kase++) cout << endl;
        for (int i = 1; i <= n; i++)
        {
            cin >> cmd;
            del.push_back(false);
            orders.push_back(Order());
            if (cmd[0] == 'C')
            {
                if (cin >> cid && !del[cid])
                {
                    if (orders[cid].in) buy_stock[orders[cid].p] -= orders[cid].q;
                    else sell_stock[orders[cid].p] -= orders[cid].q;
                    del[cid] = true;
                }
            }
            else
            {
                cin >> q >> p;
                Order x = Order(i, q, p, cmd[0] == 'B');
                orders[i] = x;
                if (x.in) buy_q.push(x), buy_stock[p] += q;
                else sell_stock[p] += q, sell_q.push(x);
            }
            exec(cmd[0]);
            cout << "QUOTE " << buy_stock[buy_q.top().p] << " " << buy_q.top().p;
            cout << " - " << sell_stock[sell_q.top().p] << " " << sell_q.top().p << endl;
        }
    }
}
