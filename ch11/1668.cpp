// UVa 1668 Let's Go Green
// wangqc
#include<iostream>

using namespace std;

const int maxn = 100005;
int n, flow[maxn], cap[maxn];

// total number of edge - max(times of merging two edges)
int main()
{
	int T;
	cin >> T;
	for(int kase = 1; kase <= T; kase++)
	{
		cin >> n;
		for(int i = 0; i <= n; i++)
			flow[i] = cap[i] = 0;
		int cnt = 0;
		for(int i = 0; i < n-1; i++)
		{
			int x, y, w;
			cin >> x >> y >> w;
			cap[x] += w;
			cap[y] += w;
			flow[x] = max(flow[x], w);
			flow[y] = max(flow[y], w);
			cnt += w;
		}
		for(int i = 1; i <= n; i++)
		{
			if(flow[i]<<1 <= cap[i]) cnt -= cap[i]>>1;
			else cnt-= cap[i]-flow[i];
		}
		printf("Case #%d: %d\n", kase, cnt);
	}
    return 0;
}
