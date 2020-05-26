// UVa 1609 Foul Play
// wangqc
#include<iostream>
#include<vector>

using namespace std;

const int maxn = 1030;
char table[maxn][maxn];

int main()
{
    int i, n;
    while (cin >> n)
    {
        for (i = 1; i <= n; i++)
            cin >> (table[i] + 1);
        vector<int> win, lose;
        for (i = 2; i <= n; i++)
        {
            if (table[1][i] == '1') win.push_back(i);
            else lose.push_back(i);
        }
        while (n >>= 1)
        {
            vector<int> win2, lose2, left;
            // find a team win[j] to defeat lose[i]
            for (int li : lose)
            {   
                bool found = false;
                for (int j = 0; !found && j < win.size(); j++)
                    if (win[j] && table[win[j]][li] == '1')
                    {
                        cout << win[j] << " " << li << endl;
                        win2.push_back(win[j]);
                        win[j] = 0;
                        found = true;
                    }
                if (!found) left.push_back(li);
            }
            // pick any win[i] to match with 1
            i = 0;
            while(!win[i]) i++;
            if (i < win.size()) 
                cout << 1 << " " << win[i++] << endl;
            for (; i < win.size(); i++) 
                if (win[i]) left.push_back(win[i]);
            // match rest teams
            for (i = 0; i < left.size(); i+=2)
            {
                cout << left[i] << " " << left[i+1] << endl;
                int x = table[left[i]][left[i+1]] == '1' ? left[i] : left[i+1];
                if (table[1][x] == '1') win2.push_back(x);
                else lose2.push_back(x);
            }
            win = win2, lose = lose2;
        }
    }
    return 0;
}
