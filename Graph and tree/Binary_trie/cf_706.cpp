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
const ll LG = 32;
struct trie
{
    trie *next[2];
    ll ocr;
    trie()
    {
        ocr = 0;
        next[0] = next[1] = NULL;
    }

} *root;

struct tree
{
    void insert(ll x)
    {
        trie *cur = root;
        for (int i = 31; i >= 0; --i)
        {
            ll bit = (x >> i) & 1;
            if (cur->next[bit] == NULL)
                cur->next[bit] = new trie();
            cur = cur->next[bit], cur->ocr++;
        }
    }
    void erase(ll x)
    {
        trie *cur = root;
        for (int i = 31; i >= 0; --i)
        {
            ll bit = (x >> i) & 1;
            cur = cur->next[bit];
            cur->ocr--;
        }
    }

    ll max_(ll x)
    {
        trie *cur = root;
        ll ans = 0;
        for (int i = 31; i >= 0; --i)
        {
            ll bit = (x >> i) & 1;
            if (cur->next[!bit] != NULL && cur->next[!bit]->ocr > 0)
            {
                ans |= (1LL << i);
                cur = cur->next[!bit];
            }
            else
            {
                cur = cur->next[bit];
            }
        }
        return ans;
    }
    void dlt(trie *cur)
    {
        if (cur == NULL)
            return;
        dlt(cur->next[0]);
        dlt(cur->next[1]);
        delete cur;
    }
} tr;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll tc = 1;

    // cin >> tc;
    while (tc--)
    {
        ll n, q;
        cin >> q;
        root = new trie();
        tr.insert(0);
        while (q--)
        {
            char ch;
            ll x;
            cin >> ch >> x;
            if (ch == '+')
                tr.insert(x);
            else if (ch == '-')
                tr.erase(x);
            else if (ch == '?')
                cout << tr.max_(x) << "\n";
            // cout << "\n";
        }
        tr.dlt(root);

        // cout << "\n";
    }

    return 0;
} // https://codeforces.com/contest/706/problem/D
