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
const ll N = 5e5 + 9;

// unique elements on the path from u to v
vector<ll> g[N];
ll st[N], en[N], T, par[N][20], dep[N], id[N * 2];
void dfs(ll u, ll p = 0)
{
    st[u] = ++T;
    id[T] = u;
    dep[u] = dep[p] + 1;
    par[u][0] = p;
    for (ll k = 1; k < 20; k++)
        par[u][k] = par[par[u][k - 1]][k - 1];
    for (auto v : g[u])
        if (v != p)
            dfs(v, u);
    en[u] = ++T;
    id[T] = u;
}
ll lca(ll u, ll v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (ll k = 19; k >= 0; k--)
        if (dep[par[u][k]] >= dep[v])
            u = par[u][k];
    if (u == v)
        return u;
    for (ll k = 19; k >= 0; k--)
        if (par[u][k] != par[v][k])
            u = par[u][k], v = par[v][k];
    return par[u][0];
}

ll cnt[N], a[N], ans;
inline void add(ll u)
{
    ll x = a[u];
    if (cnt[x]++ == 0)
        ans++;
}
inline void rem(ll u)
{
    ll x = a[u];
    if (--cnt[x] == 0)
        ans--;
}
bool vis[N];
inline void yo(ll u)
{
    if (!vis[u])
        add(u);
    else
        rem(u);
    vis[u] ^= 1;
}

const ll B = 320;
struct query
{
    ll l, r, id;
    bool operator<(const query &x) const
    {
        if (l / B == x.l / B)
            return r < x.r;
        return l / B < x.l / B;
    }
} Q[N];
ll res[N];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    cin >> tc;
    while (tc--)
    {
        ll n, q;
        cin >> n >> q;
        vector<ll> parn(n + 1);
        for (ll i = 2; i <= n; ++i)
        {
            cin >> parn[i];
            g[i].push_back(parn[i]);
            g[parn[i]].push_back(i);
        }
        string s;
        cin >> s;
        s = '#' + s;
        for (ll i = 1; i <= s.size(); ++i)
        {
            if (i == 1)
                a[i] = i;
            else
            {
                if (s[i] == '0')
                    a[i] = a[parn[i]];
                else
                    a[i] = i;
            }
        }
        T = 0;
        dfs(1);
        for (ll i = 1; i <= q; i++)
        {
            ll u, v;
            cin >> u >> v;
            if (st[u] > st[v])
                swap(u, v);
            ll lc = lca(u, v);
            if (lc == u)
                Q[i].l = st[u], Q[i].r = st[v];
            else
                Q[i].l = en[u], Q[i].r = st[v];
            Q[i].id = i;
        }
        sort(Q + 1, Q + q + 1);
        ans = 0;
        ll l = 1, r = 0;
        for (ll i = 1; i <= q; i++)
        {
            ll L = Q[i].l, R = Q[i].r;
            if (R < l)
            {
                while (l > L)
                    yo(id[--l]);
                while (l < L)
                    yo(id[l++]);
                while (r < R)
                    yo(id[++r]);
                while (r > R)
                    yo(id[r--]);
            }
            else
            {
                while (r < R)
                    yo(id[++r]);
                while (r > R)
                    yo(id[r--]);
                while (l > L)
                    yo(id[--l]);
                while (l < L)
                    yo(id[l++]);
            }
            ll u = id[l], v = id[r], lc = lca(u, v);
            if (lc != u && lc != v)
                yo(lc); // take care of the lca separately
            res[Q[i].id] = ans;
            if (lc != u && lc != v)
                yo(lc);
        }
        for (ll i = 1; i <= q; i++)
            cout << res[i] << '\n';
        for (ll i = 0; i <= n; i++)
        {
            g[i].clear();
            vis[i] = cnt[i] = 0;
            for (ll k = 0; k < 20; k++)
                par[i][k] = 0;
        }
    }
} // https://www.hackerrank.com/contests/srbd-code-contest-2023-round-1/challenges/colorful-tree-1