// UVa 1412 Fund Management
// wangqc
#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const double INF = 1e30;
const int maxn = 8, maxm = 105;
const int maxstate = 15000;

int m, n, s[maxn], k[maxn], kk;
double c, price[maxn][maxm];
char name[maxn][10];

double d[maxm][maxstate];
int op[maxm][maxstate], pre[maxm][maxstate];

int buy_next[maxstate][maxn], sell_next[maxstate][maxn];
vector<vector<int>> states;
map<vector<int>, int> ID;

void dfs(int stock, vector<int> &lots, int agg)
{
    if (stock == n)
    {
        ID[lots] = states.size();
        states.push_back(lots);
    }
    else
        for (int i = 0; i <= k[stock] && agg + i <= kk; i++)
        {
            lots[stock] = i;
            dfs(stock + 1, lots, agg + i);
        }
}

void init()
{
    vector<int> lots(n);
    states.clear();
    ID.clear();
    dfs(0, lots, 0);
    for (int s = 0; s < states.size(); s++)
    {
        int totlot = 0;
        for (int i = 0; i < n; i++)
            totlot += states[s][i];
        for (int i = 0; i < n; i++)
        {
            buy_next[s][i] = sell_next[s][i] = -1;
            if (states[s][i] < k[i] && totlot < kk)
            {
                vector<int> newstate = states[s];
                newstate[i]++;
                buy_next[s][i] = ID[newstate];
            }
            if (states[s][i] > 0)
            {
                vector<int> newstate = states[s];
                newstate[i]--;
                sell_next[s][i] = ID[newstate];
            }
        }
    }
}

void update(int day, int s, int s2, double v, int o)
{
    if (v > d[day][s2])
    {
        d[day][s2] = v;
        op[day][s2] = o;
        pre[day][s2] = s;
    }
}

double dp()
{
    for (int day = 0; day <= m; day++)
        for (int s = 0; s < states.size(); s++)
            d[day][s] = -INF;

    d[0][0] = c;
    for (int day = 0; day < m; day++)
        for (int s = 0; s < states.size(); s++) if (d[day][s] >= -1)
        {
            double v = d[day][s];
            update(day+1, s, s, v, 0); // HOLD
            for (int i = 0; i < n; i++)
            {
                if (buy_next[s][i] >= 0 && v >= price[i][day] - 1e-3)
                    update(day+1, s, buy_next[s][i], v - price[i][day], i + 1); // BUY
                if (sell_next[s][i] >= 0)
                    update(day+1, s, sell_next[s][i], v + price[i][day], -i - 1); // SELL
            }
        }
    return d[m][0];
}

void print(int day, int s)
{
    if (day == 0)
        return;
    print(day - 1, pre[day][s]);
    if (op[day][s] > 0) 
        cout << "BUY " << name[op[day][s]-1] << endl;
    else if (op[day][s] < 0) 
        cout << "SELL " << name[-op[day][s]-1] << endl;
    else cout << "HOLD\n";
}

int main()
{
    int kase = 0;
    while (cin >> c >> m >> n >> kk)
    {
        if (kase++ > 0) cout << endl;

        for (int i = 0; i < n; i++)
        {
            cin >> name[i] >> s[i] >> k[i];
            for (int j = 0; j < m; j++)
            {
                cin >> price[i][j];
                price[i][j] *= s[i];
            }
        }
        init();
        printf("%.2lf\n", dp());
        print(m, 0);
    }
    return 0;
}