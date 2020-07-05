// UVa 10213 How Many Pieces of Land ?
// wangqc
#include<iostream>

using namespace std;
// Euler formula F = E - V + 2
// V = n + nΣi(n-i-2)/4; E = n + nΣ(i(n-i-2)+1)/2
int main()
{
    int n, T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        int V = 0, E = 1;
        for(int i = 1; i <= n-2; i++)
            V += i*(n-2-i), E += i*(n-2-i)+1;
        V = V*n/4, E = E*n/2;
        cout << E - V + 1 << endl;  // exclude the background face
    }
    return 0;
}