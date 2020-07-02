// UVa 10491 Cows and Cars
// wangqc
#include<cstdio>

// P(car) = a / (a+b), P(cow|car) = b / (a+b-c-1)
// P(cow) = b / (a+b), P(cow|cow) = (b-1) / (a+b-c-1)
// P(win) = P(car)P(cow|car) + P(cow)*P(cow|cow)
int main()
{
    int a, b, c;
    while(scanf("%d%d%d", &a, &b, &c) == 3)
        printf("%.5lf\n", (double)(b*(a+b-1))/(a+b)/(a+b-c-1));
    return 0;
}
