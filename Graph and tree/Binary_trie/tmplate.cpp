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
    ll qry(ll x, ll k) // number of value s.t val^x<k
    {
        ll ans = 0;
        trie *cur = root;
        for (ll i = 31; i >= 0; i--)
        {
            if (cur == NULL)
                break;
            ll a = (x >> i) & 1;
            ll b = (k >> i) & 1;
            if (b)
            {
                if (cur->next[a])
                    ans += cur->next[a]->ocr;
                cur = cur->next[!a];
            }
            else
                cur = cur->next[a];
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

    cin >> tc;
    while (tc--)
    {
        ll n, x, y;
        cin >> n >> x >> y;
        vector<ll> v(n);
        for (auto &a : v)
            cin >> a;

        root = new trie();
        // tr.insert(0);
        ll cnt = 0;
        for (auto u : v)
        {
            cnt += tr.qry(u, y + 1) - tr.qry(u, x);
            tr.insert(u);
        }
        cout << cnt;
        tr.dlt(root);

        cout << "\n";
    }

    return 0;
}