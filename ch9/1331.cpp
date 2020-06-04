// UVa 1331 Minimax Triangulation
// wangqc
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const double INF = 1e9, eps = 1e-10;
const int maxn = 100 + 5;
double dp[maxn][maxn];
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

typedef struct Point 
{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y) {}
} Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Vector& A, const Vector& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }

bool operator < (const Point& a, const Point& b) 
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) 
{
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

bool intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
    c3 = Cross(b2-b1, a1-b1), c4=Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

bool aligned(const Point& p, const Point& a1, const Point& a2) {
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

typedef vector<Point> Polygon;

int in_polygon(const Point& p, const Polygon& poly){
    int n = poly.size(), cnt = 0;
    for(int i = 0; i < n; i++)
    {
        const Point& p1 = poly[i], p2 = poly[(i+1)%n];
        if(p1 == p || p2 == p || aligned(p, p1, p2)) return -1;
        int k = dcmp(Cross(p2-p1, p-p1));
        int d1 = dcmp(p1.y - p.y), d2 = dcmp(p2.y - p.y);
        cnt += k > 0 && d1 <= 0 && d2 > 0;
        cnt -= k < 0 && d2 <= 0 && d1 > 0;
    }
    return cnt ? 1 : 0;
}

bool is_diagonal(const Polygon& poly, int a, int b) {
    int n = poly.size();
    for(int i = 0; i < n; i++)
        if(i != a && i != b && aligned(poly[i], poly[a], poly[b])) return false;
    for(int i = 0; i < n; i++)
    if(intersect(poly[i], poly[(i+1)%n], poly[a], poly[b]))
        return false;
    return in_polygon((poly[a] + poly[b]) * 0.5, poly) == 1;
}

int main() 
{
    int m, T;
    cin  >> T;
    while (T--)
    {
        cin >> m;
        double x, y;
        Polygon poly;
        for (int i = 0; i < m; i++)
        {
            cin >> x >> y;
            poly.push_back(Point(x, y));
        }
        int n = poly.size();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) 
                dp[i][j] = -1;
        for(int i = n-2; i >= 0; i--)
            for(int j = i+1; j < n; j++) 
            {
                dp[i][j] = i + 1 == j ? 0 : INF;
                if ((i == 0 && j == n-1) || is_diagonal(poly, i, j)) 
                    for(int k = i+1; k < j; k++) 
                    {
                        double area = fabs(Cross(poly[j]-poly[i], poly[k]-poly[i])) / 2.0;
                        dp[i][j] = min(dp[i][j], max(max(dp[i][k], dp[k][j]), area));
                    }
            }
        cout << fixed << setprecision(1) << dp[0][n-1] << endl;
    }
    return 0;
}
