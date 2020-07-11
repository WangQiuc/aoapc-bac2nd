// UVa 808 Bee Breeding
// wangqc
#include<iostream>
#include<cmath>

using namespace std;
const int maxn = 20005;
// set up coordinate and use manhattan distance
const int d[6][2] = {{-1,-1},{-1,1},{0,2},{1,1},{1,-1},{0,-2}};

struct Point {
    int x, y;
    Point(int x=0, int y=0): x(x), y(y) {}
} p[maxn];

void init()
{
    int id = 1, x = 0, y = 0;
    p[id++] = Point(x++, y--);      // adjust to 1st direct
    for(int i = 1; i <= 60; i++)
    {
        for(int j = 0; j <= 5; j++)
            for(int k = 0; k < i; k++)
                p[id++] = Point(x+=d[j][0], y+=d[j][1]);
        x++, y--;                   // adjust to 1st direct
    }
}

int main()
{
    init();
    int a, b;
    while(cin >> a >> b && a)
    {
        int x = abs(p[a].x - p[b].x);
        int y = abs(p[a].y - p[b].y);
        printf("The distance between cells %d and %d is %d.\n", a, b, (x>=y ? x : (x+y)>>1));
    }
    return 0;
}
