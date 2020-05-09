// UVa10953 Throwing Cards Away I
// wangqc

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        queue<int> q;
        for (int i = 1; i <= n; i++) q.push(i);
        cout << "Discarded cards: ";
        while (q.size() > 2)
        {
            cout << q.front() << ", ";
            q.pop();
            q.push(q.front());
            q.pop();       
        }
        cout << q.front() << endl;
        q.pop();
        cout << "Remaining card: " << q.front() << endl;
    }
    return 0;
}
