// UVa230 Borrowers
// wangqc

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Book 
{
    string author;
    int status = 1;
    Book(): author(), status() {}  // STL container needs a default constructor
    Book(string a, int s): author(a), status(s) {}
};

vector<string> books;
map<string, Book> catalog;

bool cmp(string a, string b)
{
    if (catalog[a].author == catalog[b].author) return a < b;
    return catalog[a].author < catalog[b].author;
}

int main()
{
    string cmd, name, author;
    while (getline(cin, cmd) && cmd != "END")
    {    
        int i = cmd.find('\"', 1);
        name = cmd.substr(0, i+1);
        books.push_back(name);
        catalog[name] = Book(cmd.substr(i+5), 1);
    }
    sort(books.begin(), books.end(), cmp);
    while (cin >> cmd && cmd != "END")
    {
        if (cmd != "SHELVE")
        {
            getchar();
            getline(cin, name);
            catalog[name].status = cmd == "BORROW" ? -1 : 0;
        }
        else
        {
            for (int i = 0; i < books.size(); i++)
                if (!catalog[books[i]].status)  // return but not on shelf
                {
                    cout << "Put " << books[i];
                    int j = i;
                    while (j >= 0 && catalog[books[j]].status != 1) j--;
                    if (j == -1) cout << " first" << endl; 
                    else cout << " after " << books[j] << endl;
                    catalog[books[i]].status = 1;
                }
            cout << "END" << endl;
        } 
    }
    return 0;
}
