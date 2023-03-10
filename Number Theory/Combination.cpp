//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef vector<pair<ll, ll>> vli;
typedef double dl;
typedef map<ll, ll> mp;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fixed, ios::floatfield);
//////////////////////////////Debug part////////////////////////////////////

template <typename F, typename S>
ostream &operator<<(ostream &os, const pair<F, S> &p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename F, typename S>
ostream &operator<<(ostream &os, const map<F, S> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << it->first << " = " << it->second;
    }
    return os << "]";
}

#define dbg(args...)            \
    do                          \
    {                           \
        cerr << #args << " : "; \
        faltu(args);            \
    } while (0)

void faltu()
{
    cerr << endl;
}

template <typename T>
void faltu(T a[], ll n)
{
    for (ll i = 0; i < n; ++i)
        cerr << a[i] << ' ';
    cerr << endl;
}

template <typename T, typename... hello>
void faltu(T arg, const hello &...rest)
{
    cerr << arg << ' ';
    faltu(rest...);
}
///////////////////////
const ll MOD = 998244353;
const ll mx = 2e5 + 1;
ll fact[mx];
ll inv[mx];
struct combin
{

    inline void normal(ll &a)
    {
        a %= MOD;
        (a < 0) && (a += MOD);
    }
    inline ll modMul(ll a, ll b)
    {
        a %= MOD, b %= MOD;
        normal(a), normal(b);
        return (a * b) % MOD;
    }
    inline ll modAdd(ll a, ll b)
    {
        a %= MOD, b %= MOD;
        normal(a), normal(b);
        return (a + b) % MOD;
    }
    inline ll modSub(ll a, ll b)
    {
        a %= MOD, b %= MOD;
        normal(a), normal(b);
        a -= b;
        normal(a);
        return a;
    }
    inline ll modPow(ll b, ll p)
    {
        ll r = 1;
        while (p)
        {
            if (p & 1)
                r = modMul(r, b);
            b = modMul(b, b);
            p >>= 1;
        }
        return r;
    }
    inline ll modInverse(ll a) { return modPow(a, MOD - 2); }
    inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }

    ll C(ll n, ll r)
    {
        if (n < 0 or r < 0 or r > n)
            return 0;
        ll ret = 1LL * modMul(fact[n], inv[r]);
        ret = 1LL * modMul(ret, inv[n - r]);
        return ret;
    }
    // X1 + X2 + ... + Xvar = Sum
    ll no_of_eqns(int sum, int var)
    {
        return C(sum + var - 1, var - 1); // Xi >= 0
        // return C(sum-1,var-1); // Xi > 0
    }
    void init()
    {
        fact[0] = 1;
        for (ll i = 1; i < mx; i++)
            fact[i] = 1LL * modMul(fact[i - 1], i);

        inv[mx - 1] = modInverse(fact[mx - 1]);
        for (ll i = mx - 2; i >= 0; i--)
            inv[i] = 1LL * modMul(inv[i + 1], (i + 1));
    }

} com;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    com.init();
    // cin >> tc;
    while (tc--)
    {
        ll n;
        cin >> n;
        ll x = 1;
        for (int i = 1; i <= n / 3; i++)
        {
            ll a, b, c;
            cin >> a >> b >> c;
            set<ll> s;
            s.insert(a);
            s.insert(b);
            s.insert(c);
            ll mn = min({a, b, c});
            ll cnt = 0;
            if (a == mn)
                cnt++;
            if (b == mn)
                cnt++;
            if (c == mn)
                cnt++;
            if (s.size() == 1)
                x = com.modMul(x, 3LL);
            else if (s.size() == 2 && cnt == 2)
                x = com.modMul(x, 2LL);
        }
        ll res = com.C(n / 3, n / 6);
        res = com.modMul(res, x);
        cout << res;

        cout << "\n";
    }

    return 0;
} // https://codeforces.com/contest/1795/problem/D