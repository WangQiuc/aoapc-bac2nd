// UVa 10954 Add All
// wangqc
#include<iostream>
#include<queue>

using namespace std;

int main()
{
    int n, x;
    while (cin >> n && n)
    {
        priority_queue<int ,vector<int>, greater<int> > pq;
        for (int i = 0; i < n; i++) 
        {
            cin >> x;
            pq.push(x);
        }
        int cost = 0;
        for (int i = 0; i < n-1; i++)
        {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            cost += a + b;
            pq.push(a + b);
        }
        cout << cost << endl;
    }
    return 0;
}
