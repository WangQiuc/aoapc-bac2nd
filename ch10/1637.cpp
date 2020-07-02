// UVa 1637 Double Patience
// wangqc
#include<iostream>
#include<vector>
#include<map>

using namespace std;

map<vector<int>, double> d;
char card[9][4][3];

double dp(vector<int> &cnt, int k)
{
    if(k == 0) return 1;
    if(d.count(cnt)) return d[cnt];
    double sum = 0;
    int tot = 0;
    for(int i = 0; i < 9; i++) if(cnt[i])
        for(int j = i+1; j < 9; j++) if(cnt[j])
            if(card[i][cnt[i]-1][0] == card[j][cnt[j]-1][0])    // pile i and pile j have same rank
            {
                tot++, cnt[i]--, cnt[j]--;
                sum += dp(cnt, k-2);
                cnt[i]++, cnt[j]++;
            }
    if(tot == 0) return d[cnt] = 0;
    else return d[cnt] = sum / tot;
}

bool read()
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 4; j++)
            if(!(cin >> card[i][j])) return false;
    return true;
}

int main()
{
    while(read())
    {
        vector<int> cnt(9, 4);
        d.clear();
        printf("%.6lf\n", dp(cnt, 36));
    }
    return 0;
}
