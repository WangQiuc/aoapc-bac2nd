// wangqc
#include<iostream>

using namespace std;

const int maxn = 10;
int A[maxn];
int P[maxn];

void print_permutation(int n, int *A, int *P, int cur)
{
    if (cur == n)
    {
        for (int i = 0; i < n; i++) cout << A[i] << " ";
        cout << endl;
    }
    else for (int i = 0; i < n; i++)
    {
        if (!i || P[i] != P[i-1])
        {
            int c1 = 0, c2 = 0;
            for (int j = 0; j < cur; j++)
                c1 += A[j] == P[i];
            for (int j = 0; j < n; j++)
                c2 += P[j] == P[i];
            if (c1 < c2) 
            {
                A[cur] = P[i];
                print_permutation(n, A, P, cur+1);
            }
        }
    }
}

// input:
// n: P.length()
// P1 P2 ... Pn 
// Example:
// 3
// 1 2 3
// 3
// 1 1 1
// 4
// 1 1 2 2

int main()
{
    int n, x;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            A[i] = 0, P[i] = x;
        }
        print_permutation(n, A, P, 0);
        cout << endl;
    }
    return 0;
}
