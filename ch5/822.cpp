// UVa822 Queue and A
// wangqc

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 0x7fffffff;
struct topic 
{
    int cnt, t, dt, nt; // t current time, dt serving time, nt next request time
    topic() {}
    topic(int cnt, int t, int dt, int nt): cnt(cnt), t(t), dt(dt), nt(nt) {}
};
struct agent
{
    int id, t, pt;
    vector<int> lst;
    agent() {}
    agent(string s) 
    {
        t = pt = 0;
        int k, x;
        stringstream ss(s);
        ss >> id >> k;
        while (k--) { ss >> x; lst.push_back(x); }
    }
    bool operator < (const agent rhs) const
    {
        return pt < rhs.pt || (pt == rhs.pt && id < rhs.id);
    }
};

int main()
{
    int n, m, kase = 0;
    string s;
    while (cin >> n && n)
    {
        int ts = INF, ans = 0;  // current timestamp; finish time
        map<int, topic> topics;
        vector<agent> agents;
        for (int i = 0; i < n; i++)
        {
            int tid, cnt, t, dt, nt;
            cin >> tid >> cnt >> t >> dt >> nt;
            topics[tid] = topic(cnt, t, dt, nt);
            ts = min(ts, t);    
        }
        cin >> m; getchar();
        while(m--)
        {
            getline(cin, s);
            agents.push_back(agent(s));
        }
        while (n)
        {
            sort(agents.begin(), agents.end());
            int next_t = INF;
            for (agent &a : agents)
            {
                if (a.t <= ts)                              // a is available
                {
                    a.t = INF;
                    for (int j : a.lst)
                        if (topics[j].cnt)
                        {
                            topic &x = topics[j];
                            if (x.t <= ts)
                            {
                                a.pt = ts, a.t = ts + x.dt; // a did x at ts
                                ans = max(ans, a.t);
                                x.cnt--, x.t += x.nt;
                                if (!x.cnt) n--;            // x is completed
                                break;
                            }
                            a.t = min(a.t, x.t);            // if a did nothing
                        }
                }
                next_t = min(next_t, a.t); 
            }
            ts = next_t;              // ts jmp to next available agent's time
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", ++kase, ans);
    }
    return 0;
}
