// UVa 12174 Shuffle
// wangqc
#include<iostream>
#include<vector>

using namespace std;

const int maxn = 100005;

// A - last played track, B - current playing tracks, C - next unplayed track
// x[maxn*3] = [A] + [B](the given x1-xn) + [C]
int s, n, x[maxn*3], ctr[maxn];
bool start[maxn*2];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> s >> n;
        fill(x, x+n+2*s, -1);
        for (int i = 0; i < n; i++)
            cin >> x[i+s];
        int songs = 0;
        fill(ctr+1, ctr+s+1, 0);
        fill(start, start+n+s+1, 0);
        for (int i = 0; i < n+s ; i++)
        {   // all songs in window are unique
            start[i] = (songs == s) || (i < s && songs == i) || (i > n && songs == n+s-i);
            if (x[i] != -1 && --ctr[x[i]] == 0) songs--;    // slide out
            if (x[i+s] != -1 && ctr[x[i+s]]++ == 0) songs++;  // slid in
        }
        start[n+s] = !songs;
        int cnt = 0;
        for (int i = 0; i < s; i++)
        {   // start at i
            bool ok = true;
            for (int j = i; ok && j < n+s+1; j += s)
                ok = start[j];
            if (ok) cnt++;
        }
        if (cnt == n+1) cnt = s;
        cout << cnt << endl;
    }
    return 0;
}
