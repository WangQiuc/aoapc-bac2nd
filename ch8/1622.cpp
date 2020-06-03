// UVa 1622 Robot
// wangqc
#include<iostream>
#include<algorithm>

using namespace std;

typedef long long LL;

int main()
{
    int kase = 0;
    LL n, m;
    while (cin >> n >> m, m || n)
    {
        LL cn, cs, cw, ce, cnt = 0;
        cin >> cn >> cs >> cw >> ce;
        // make cn > cs, cw > ce, won't effect result as n*m matrix is symmetry
        if (cn < cs) swap(cn, cs);
        if (cw < ce) swap(cw, ce);
        // cnt when first move e <-> w then s <-> n
        LL c1 = n+(m-1)*n*(ce*2+(cw!=ce)) + (m-1)+(m-1)*(n-1)*(cs*2+(cn!=cs));
        // cnt when first move s <-> n then e <-> w
        LL c2 = m+(n-1)*m*(cs*2+(cn!=cs)) + (n-1)+(n-1)*(m-1)*(ce*2+(cw!=ce));
        // make sure should first move e <-> w then s <-> n to maximize cnt
        if (c1 < c2) swap(n, m), swap(cn, cw), swap(cs, ce);
        if (cw) cnt = n+(m-1)*n*(ce*2+(cw!=ce)), cw = min(--m, cw-ce-(cw!=ce)), ce = 0;
        while (cw || cn)
        {
            if (cs)
            {
                c1 = m*n+(n-1)*m*(cs*2+(cn!=cs)), c2 = m*n+(m-1)*n+(m-1)*(n-1)*(cs*2-(cn==cs));
                if (c1 <= c2 && cw) cnt += m*n, m--, cw--;
                else cnt += m+m*(n-1)*(cs*2+(cn!=cs)), cn = min(--n, cn-cs-(cn!=cs)), cs = 0;
            }
            else if(!cw) cnt += m*cn*(n*2-cn+1)/2, cn=0;
            else if(!cn) cnt += n*cw*(m*2-cw+1)/2, cw=0;
            else{
                cnt += m*n;
                if(m > n) m--, cw--;
                else n--, cn--;
            }
        }
        cout << "Case " << ++kase << ": " << cnt << endl;
    }
    return 0;
}
