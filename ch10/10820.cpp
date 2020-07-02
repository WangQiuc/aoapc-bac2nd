// UVa 10820 Send a Table
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 50000;
int phi[maxn+1], phi_s[maxn+1];

// phi[x] = x*(1-1/p1)*...*(1-1/pn), p1...pn is prime factor of x
void gen_phi()
{
    phi[1] = 0;
    for(int i = 2; i <= maxn; i++) if(!phi[i]) // i is a prime
        for(int j = i; j <= maxn; j += i)
        {
            if(!phi[j]) phi[j] = j;         // i is a prime factor of j
            phi[j] = phi[j]/i*(i-1);
        }
}

int main()
{
    gen_phi();
    phi_s[0] = 0;
    for(int i = 1; i <= maxn; i++)
        phi_s[i] = phi_s[i-1] + phi[i];
    int n;
    while(cin >> n && n)
        cout << (phi_s[n]<<1)+1 << endl;
    return 0;
}
