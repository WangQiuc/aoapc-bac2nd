// UVa 1641 ASCII Area
// wangqc
#include<iostream>
#include<cstring>

using namespace std;

// oddth '/\' enter area; eventh '/\' exit area
int main()
{
    int h, w;
    char s[105];
    while(cin >> h >> w)
    {
        int ans = 0;
        while(h--)
        {
            bool in = false;
            cin >> s;
            for(int i = 0; i < w; i++)
            {   // border cell only contain half area
                if(s[i]=='/'||s[i]=='\\') ans++, in = !in;
                else if(in) ans += 2;
            }
        }
        cout << (ans>>1) << endl;
    }
}
