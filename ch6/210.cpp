// UVa210 Concurrency Simulator
// wangqc

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

deque<int> waitq;
queue<int> blockq;
int n, qnt, t[5], var[26];
vector<int> ps;
vector<string> cmd;
bool locked;

void exec(int pid)
{
    int q = qnt;
    while (q > 0)
    {
        string p = cmd[ps[pid]];
        if (p[2] == '=')  // {var} = {const}
        {
            var[p[0]-'a'] = p.length() == 6 ? (p[4]-'0')*10+(p[5]-'0') : p[4]-'0';
            q -= t[0];
        }
        else if (p[2] == 'i')  // print {var}
        {
            printf("%d: %d\n", pid+1, var[p[6]-'a']);
            q -= t[1];
        }
        else if (p[2] == 'c')  // lock
        {
            if (locked) { blockq.push(pid); return; }
            locked = true;
            q -= t[2];
        }
        else if (p[2] == 'l')  // unlock
        {
            locked = false;
            if (!blockq.empty())
            {
                waitq.push_front(blockq.front());
                blockq.pop();
            }
            q -= t[3];
        }
        else return;           // end 
        ps[pid]++;
    }
    waitq.push_back(pid);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        scanf("%d%d%d%d%d%d%d\n", &n, &t[0], &t[1], &t[2], &t[3], &t[4], &qnt);
        memset(var, 0, sizeof(var));
        vector<int>().swap(ps);
        vector<string>().swap(cmd);
        int ip = 0;
        string s;
        for (int i = 0; i < n; i++)
        {
            ps.push_back(ip);
            do
            {
                getline(cin, s);
                cmd.push_back(s);
                ip++;
            } 
            while (s[2] != 'd');    // could be {var} = 'e'
            waitq.push_back(i);
        }
        locked = false;
        while (!waitq.empty())
        {
            int pid = waitq.front();
            waitq.pop_front();
            exec(pid);
        }
        if (T) cout << endl;
    }
    return 0;
}
