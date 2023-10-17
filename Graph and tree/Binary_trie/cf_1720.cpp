//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef double dl;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define MOD 1000000007

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);

//////////////////////////////-------->
const ll mx = 3e5 + 10;
ll LG = 31;
struct trie
{
    trie *next[2];
    ll len[2];
    trie()
    {
        len[0] = len[1] = 0;
        next[0] = next[1] = NULL;
    }
} *root;

struct tree
{
    void insert(ll val, ll idx, ll len)
    {
        ll x = val ^ idx;
        trie *cur = root;
        for (ll i = LG - 1; i >= 0; i--)
        {
            ll a = (x >> i) & 1;
            ll b = (idx >> i) & 1;
            if (cur->next[a] == NULL)
            {
                cur->next[a] = new trie();
            }
            cur = cur->next[a];
            cur->len[b] = max(len, cur->len[b]);
        }
    }

    ll get(ll x, ll i)
    {
        ll opt = 0;
        ll val = x ^ i;
        trie *cur = root;
        for (ll j = LG - 1; j >= 0; j--)
        {
            ll bit = (val >> j) & 1;
            ll ibit = (i >> j) & 1;
            ibit ^= bit;
            if (cur->next[bit ^ 1])
            {
                opt = max(opt, cur->next[bit ^ 1]->len[ibit]);
            }
            if (cur->next[bit])
            {
                cur = cur->next[bit];
            }
            else
                break;
        }
        return opt + 1;
    }
    void deleteTrie(trie *cur)
    {
        if (cur == NULL)
            return;
        deleteTrie(cur->next[0]);
        deleteTrie(cur->next[1]);
        delete cur;
    }
} tr;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        ll n;
        cin >> n;
        vl v(n);
        for (auto &a : v)
            cin >> a;

        ll mx = 0;
        root = new trie();
        for (ll i = n - 1; i >= 0; i--)
        {
            ll now = tr.get(v[i], i);
            tr.insert(v[i], i, now);
            mx = max(mx, now);
        }
        tr.deleteTrie(root);
        cout << mx;

        cout << "\n";
    }

    return 0;
}