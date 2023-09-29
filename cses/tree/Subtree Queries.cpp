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
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

///////////bit-manipulation///////////////
#define MSB(mask) 63 - __builtin_clzll(mask)
#define LSB(mask) __builtin_ctzll(mask)
#define ONE(mask) __builtin_popcountll(mask)
#define CHECK(mask, bit) (mask & (1LL << bit))
#define ON(mask, bit) (mask | (1LL << bit))
#define OFF(mask, bit) (mask & ~(1LL << bit))
#define CHANGE(mask, bit) (mask ^ (1LL << bit))

#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);
//////////////////////////////////
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

//////////////////////
const ll N = 2e5 + 10;

vl g[N];
ll a[N], tim, in[N], out[N], per[N], v[N];
ll n, q;

struct st
{
    ll t[4 * N];
    void build(ll nod, ll a, ll b)
    {

        if (a == b)
        {
            t[nod] = (v[a]);
            return;
        }
        ll mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = t[nod << 1] + t[nod << 1 | 1];
    }
    void update(ll nod, ll a, ll b, ll l, ll r, ll x)
    {
        if (r < a || b < l)
            return;
        if (l <= a && b <= r)
        {
            t[nod] = x;
            return;
        }

        ll mid = (a + b) >> 1;
        update(nod << 1, a, mid, l, min(r, mid), x);
        update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = t[nod << 1] + t[nod << 1 | 1];
    }

    ll query(ll nod, ll a, ll b, ll l, ll r)
    {
        if (r < a || b < l)
            return 0;

        if (l <= a && b <= r)
        {
            return t[nod];
        }

        ll mid = (a + b) >> 1;
        return query(nod << 1, a, mid, l, r) + query(nod << 1 | 1, mid + 1, b, l, r);
    }
} seg;

void dfs(ll node, ll p)
{
    in[node] = ++tim;
    v[tim] = a[node];
    per[node] = p;
    for (auto u : g[node])
    {
        if (u != p)
        {
            dfs(u, node);
        }
    }
    out[node] = tim;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--)
    {
        cin >> n >> q;
        for (ll i = 1; i <= n; i++)
            cin >> a[i];
        for (ll i = 1; i < n; ++i)
        {
            ll u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, -1);
        seg.build(1, 1, n);

        while (q--)
        {
            ll ty, s, x;
            cin >> ty;
            if (ty == 1)
            {
                cin >> s >> x;
                seg.update(1, 1, n, in[s], in[s], x);
            }
            else
            {
                cin >> s;
                cout << seg.query(1, 1, n, in[s], out[s]) << "\n";
            }
        }
    }
} // https://cses.fi/problemset/task/1137