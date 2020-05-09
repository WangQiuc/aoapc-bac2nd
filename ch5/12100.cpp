// UVa12100 Printer Queue
// wangqc

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        priority_queue<int, vector<int> >pq;
        queue<int> q;
        int n, i, x, cnt = 0;
        cin >> n >> i;
        for (int j = 0; j < n; j++) 
        {
            cin >> x;
            pq.push(x);
            q.push(x);
        }
        while (1)
        {
            if (pq.top() == q.front())
            {
                cnt++;
                if (!(i--)) break;
                pq.pop(); q.pop();
            }
            else 
            {
                if (!(i--)) i = q.size() - 1;
                q.push(q.front()); q.pop();
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
