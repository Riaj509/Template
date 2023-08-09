//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long int ll;
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
const ll N = 2e5 + 9, LG = 20;

struct edge
{
    ll u, v, cost, id;
};

vector<pair<ll, ll>> g[N];
vector<edge> eg;
ll par[N][LG + 1], dep[N], sz[N], mx[N][LG + 1];

struct dsu
{
    vector<ll> par, rnk, size;
    ll c;
    dsu(ll n) : par(n + 1), rnk(n + 1, 0), size(n + 1, 1), c(n)
    {
        for (ll i = 1; i <= n; ++i)
            par[i] = i;
    }
    ll find(ll i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
    bool same(ll i, ll j) { return find(i) == find(j); }
    ll get_size(ll i) { return size[find(i)]; }
    ll count() { return c; } // connected components
    ll merge(ll i, ll j)
    {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j])
            swap(i, j);
        par[i] = j;
        size[j] += size[i];
        if (rnk[i] == rnk[j])
            rnk[j]++;
        return j;
    }
};
void dfs(ll u, ll p) // u==3,p==1
{
    par[u][0] = p;
    // dep[u] = dep[p] + 1;
    sz[u] = 1;
    // mx[u][0] = 0;
    for (ll i = 1; i <= LG; i++)
    {
        par[u][i] = par[par[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[par[u][i - 1]][i - 1]);
    }
    for (auto v : g[u])
        if (v.first != p)
        {
            mx[v.first][0] = v.second;
            dep[v.first] = dep[u] + 1;
            dfs(v.first, u);
            sz[u] += sz[v.first];
        }
}
ll lca(ll u, ll v)
{
    ll ans = 0;
    if (dep[u] < dep[v])
        swap(u, v);
    for (ll k = LG; k >= 0; k--)
        if (dep[par[u][k]] >= dep[v])
        {
            ans = max(ans, mx[u][k]);
            u = par[u][k];
        }
    if (u == v)
        return ans;
    for (ll k = LG; k >= 0; k--)
    {
        if (par[u][k] != par[v][k])
        {
            ans = max({ans, mx[u][k], mx[v][k]});
            u = par[u][k];
            v = par[v][k];
        }
    }
    ans = max({ans, mx[u][0], mx[v][0]});
    return ans;
}
ll kth(ll u, ll k)
{
    assert(k >= 0);
    for (ll i = 0; i <= LG; i++)
        if (k & (1 << i))
            u = par[u][i];
    return u;
}
ll dist(ll u, ll v)
{
    ll l = lca(u, v);
    return dep[u] + dep[v] - (dep[l] << 1);
}
// kth node from u to v, 0th node is u
ll go(ll u, ll v, ll k)
{
    ll l = lca(u, v);
    ll d = dep[u] + dep[v] - (dep[l] << 1);
    assert(k <= d);
    if (dep[l] + k <= dep[u])
        return kth(u, k);
    k -= dep[u] - dep[l];
    return kth(v, dep[v] - dep[l] - k);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--)
    {
        ll n, m;
        cin >> n >> m;

        ll p[m + 1], q[m + 1], wt[m + 1];
        for (ll i = 1; i <= m; i++)
        {
            cin >> p[i] >> q[i] >> wt[i];
            eg.push_back({p[i], q[i], wt[i], i});
        }
        sort(all(eg), [&](edge &a, edge &b)
             { return a.cost < b.cost; });
        ll ans = 0;
        vector<ll> used(m + 1, 0);
        dsu ds(n);
        for (auto a : eg)
        {
            ll x = a.u, y = a.v, cst = a.cost, use = a.id;
            if (ds.same(x, y))
                continue;
            ds.merge(x, y);
            ans += cst;
            used[use] = 1;
            g[x].push_back({y, cst});
            g[y].push_back({x, cst});
        }
        // cout << ans << "\n";
        dfs(1, 1);

        for (ll i = 1; i <= m; i++)
        {
            if (used[i])
                cout << ans << "\n";
            else
                cout << ans + wt[i] - lca(p[i], q[i]) << "\n";
        }
    }

    return 0;
} // https://codeforces.com/contest/609/problem/E