// UVa 1636 Headshot
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

char s[120];

int main()
{
    while(cin >> s)
    {   // a - # of "00", SHOOT; b - # of "0", ROTATE
        int a = 0, b = 0, n = strlen(s);
        for(int i = 0; i < n; i++) if(s[i] == '0')
        {
            b++;
            if(s[(i+1)%n] == '0') a++;
        }   // a/b(shoot after a "0"), b/n(random pick a "0")
        if(a*n > b*b) cout << "SHOOT\n";
        else if(a*n < b*b) cout << "ROTATE\n";
        else cout << "EQUAL\n";
    }
    return 0;
}
