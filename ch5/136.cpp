// UVa136 Ugly Number
// wangqc

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef long long LL;
const int coeff[3] = {2, 3, 5};

int main()
{
    priority_queue<LL, vector<LL>, greater<LL> > pq;
    set<LL> seen;
    pq.push(1);
    seen.insert(1);
    for (int i = 1; i < 1500; i++)
    {
        LL x = pq.top(); pq.pop();
        for (int j = 0; j < 3; j++)
        {
            LL x2 = x * coeff[j];
            if (!seen.count(x2))
            {
                pq.push(x2);
                seen.insert(x2);
            }
        }
    }
    cout << "The 1500'th ugly number is " << pq.top() << "." << endl;
    return 0;
}
