// UVa 1262 Password
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

char p[2][6][5], valid[6][5];
int comb[6], cnt[5];
bool vis[2][26];

int main()
{
    comb[5] = 1;
    int k, T;
    cin >> T;
    while(T--)
    {
        memset(cnt, 0, sizeof(cnt));
        cin >> k;
        k--;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 6; j++)
                cin >> p[i][j];
        for(int i = 0; i < 5; i++)
        {
            memset(vis, 0, sizeof(vis));
            for(int j = 0; j < 2; j++)
                for(int k = 0; k < 6; k++)
                    vis[j][p[j][k][i]-'A'] = true;
            for(int j = 0; j < 26; j++) if(vis[0][j] && vis[1][j]) 
                valid[i][cnt[i]++] = 'A' + j;
        }
        for(int i = 4; i >= 0; i--)
            comb[i] = comb[i+1]*cnt[i];
        if(k >= comb[0]) cout << "NO\n";
        else
        {
            for(int i = 0; i < 5; i++)
            {
                cout << valid[i][k / comb[i+1]];
                k %= comb[i+1];
            }
            cout << endl;
        }
    }
    return 0;
}
