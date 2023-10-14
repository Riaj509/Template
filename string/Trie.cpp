//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (ll) x.size()
#define mem(a, b) memset(a, b, sizeof a)
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define eps 1e-10
/////////////////

/////////////////////////
struct trie
{
    trie *next[26];
    bool is;
    trie()
    {
        is = false;
        for (int i = 0; i < 26; ++i)
            next[i] = NULL;
    }

} *root;

struct tree
{
    void insert(string &s)
    {
        trie *cur = root;
        for (int i = 0; i < s.size(); ++i)
        {
            int ch = s[i] - 'a';
            if (cur->next[ch] == NULL)
                cur->next[ch] = new trie();
            cur = cur->next[ch];
        }
        cur->is = true;
    }

    bool check(string &s)
    {
        trie *cur = root;
        for (int i = 0; i < s.size(); ++i)
        {
            int ch = s[i] - 'a';
            if (cur->next[ch] == NULL)
                return false;
            cur = cur->next[ch];
        }
        return cur->is;
    }
    void dlt(trie *cur)
    {
        if (cur == NULL)
            return;
        for (int i = 0; i < 26; ++i)
        {
            dlt(cur->next[i]);
        }
        delete cur;
    }
} tr;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll tc = 1;

    cin >> tc;
    while (tc--)
    {
        ll n;
        cin >> n;
        root = new trie();
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;
            tr.insert(s);
        }
        ll q;
        cin >> q;
        while (q--)
        {
            string p;
            cin >> p;
            if (tr.check(p))
                cout << "YES";
            else
                cout << "NO";
            cout << "\n";
        }
        tr.dlt(root);

        cout << "\n";
    }

    return 0;
}
