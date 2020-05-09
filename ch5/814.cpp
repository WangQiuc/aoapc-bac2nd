// UVa814 The Letter Carrier's Rounds
// wangqc

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

void parse_addr(const string &s, string &user, string &mta)
{
    int a = s.find('@');
    user = s.substr(0, a);
    mta = s.substr(a+1);
}

int main()
{
    int n;
    string s, t, user1, mta1, user2, mta2;
    set<string> valid_addr;
    while (cin >> s && s != "*")
    {
        cin >> s >> n;
        while (n--)
        {
            cin >> t;
            valid_addr.insert(t + "@" + s);
        }
    }
    while (cin >> s && s != "*")
    {
        parse_addr(s, user1, mta1);
        vector<string> recv_mta;
        map<string, vector<string> > recv_addr;
        set<string> v;
        while (cin >> t && t != "*")
        {
            if (v.count(t)) continue;
            v.insert(t);
            parse_addr(t, user2, mta2);
            if (!recv_addr.count(mta2)) 
            {
                recv_mta.push_back(mta2);
                recv_addr[mta2] = vector<string>();
            }
            recv_addr[mta2].push_back(t);
        }
        getline(cin, t);
        string data;
        while (getline(cin, t) && t[0] != '*')
            data += "     " + t + "\n";
        for (int i = 0; i < recv_mta.size(); i++)
        {
            string mta2 = recv_mta[i];
            vector<string> users = recv_addr[mta2];
            cout << "Connection between " << mta1 << " and " << mta2 << endl;
            cout << "     HELO " << mta1 << "\n     250\n";
            cout << "     MAIL FROM:<" << s << ">\n     250\n";
            bool ok = false;
            for (int j = 0; j < users.size(); j++)
            {
                cout << "     RCPT TO:<" << users[j] << ">\n";
                if (valid_addr.count(users[j])) { ok = true; cout << "     250\n"; }
                else cout << "     550\n";
            }
            if (ok) cout << "     DATA\n     354\n" << data << "     .\n     250\n";
            cout << "     QUIT\n     221\n";
        }
    }
    return 0;
}
