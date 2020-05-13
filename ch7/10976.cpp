// UVa 10976 Fractions Again?!
// wangqc
#include<cstdio>
#include<vector>

using namespace std;

// 1/k = 1/x + 1/y, x >= y, 1/k <= 2/y, y <= 2k, x = ky / (y-k)
int main()
{
    int n, k;
    while (scanf("%d", &k) == 1 && k)
    {
        vector<int> X, Y;
        for (int y = k+1; y <= k<<1; y++)
            if (!(k*y % (y-k))) 
                X.push_back(k*y / (y-k)), Y.push_back(y);
        n = X.size();
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
            printf("1/%d = 1/%d + 1/%d\n", k, X[i], Y[i]);
    }
    return 0;
}
