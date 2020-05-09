// UVa806 Spatial Structures
// wangqc

#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

const int maxn = 64;
char pic[maxn][maxn];
vector<int> seq;        // need a vector to perform sorting

void seq2pic(int n)
{
    memset(pic, '.', sizeof(pic));
    int dec;
    while(cin >> dec && dec != -1)
    {
        int x = 0, y = 0, len = n;
        while(dec)
        {
            int d = dec % 5; dec /= 5;
            len >>= 1;
            if (d > 2) x += len;        // d == 3 || 4, sw || se
            if (!(d & 1)) y += len;     // d == 2 || 4, ne || se
        }
        for (int i = x; i < x + len; i++)
            for (int j = y; j < y + len; j++)
                pic[i][j] = '*';    
    }
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
            cout << pic[i][j];
    }
    cout << endl;
}

void dfs(int x, int y, int len, int base, int dec)
{
    int flag = 0;  // 01-has black, 10-has white; 11-has both
    for (int i = x; i < x + len && flag != 3; i++)
        for (int j = y; j < y + len && flag != 3; j++)
            flag |= 1 << ('1' - pic[i][j]);
    if (flag == 1) seq.push_back(dec);
    if (flag == 3)
    {
        len >>= 1;
        dfs(x,     y,     len, base*5, dec + base);         // nw - 1
        dfs(x,     y+len, len, base*5, dec + base*2);       // ne - 2
        dfs(x+len, y,     len, base*5, dec + base*3);       // sw - 3
        dfs(x+len, y+len, len, base*5, dec + base*4);       // se - 4
    }

}

void pic2seq(int n)
{
    seq.clear();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> pic[i][j];       
    dfs(0, 0, n, 1, 0);
    sort(seq.begin(), seq.end());
    for (int i = 0; i < seq.size(); i++)
    {
        if (!(i % 12)) cout << endl << seq[i];
        else cout << " " << seq[i];
    }
    cout << endl << "Total number of black nodes = " << seq.size() << endl;
}

int main()
{
    int n, kase = 0;
    while (cin >> n && n)
    {
        if (kase++) cout << endl;
        cout << "Image " << kase;
        if (n > 0) pic2seq(n);
        else seq2pic(-n);
    }
    return 0;
}
