// UVa10410 Tree Reconstruction
// wangqc
#include<iostream>
#include<vector>
#include<stack>

using namespace std; 

int main()
{
    int n;
    while (cin >> n && n)
    {
        int x, idx[n+1];
        vector<int> graph[n+1];
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            idx[x] = i;
        }
        stack<int> st;
        cin >> x; st.push(x);
        for (int i = 1; i < n; i++)
        {
            cin >> x; st.push(x);
            for (;;)
            {
                int p = st.top();
                if (st.size() == 1 || idx[p] + 1 < idx[x])  // p is x parent
                {
                    graph[p].push_back(x);
                    st.push(x);
                    break;
                }
                else st.pop();
            }
        }
        for (int i = 1; i <= n; i++)
        {
            cout << i << ":";
            for (int x : graph[i]) cout << " " << x;
            cout << endl;
        }
    }
    return 0;
}
