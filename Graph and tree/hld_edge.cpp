//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (ll) x.size()
#define mem(a) memset(a, 0, sizeof a)
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
///////////////////////////////
// 1 i w : Change the weight of edge i to  w.
// 2 u v：Print the distance between vertex u and vertex v.
const ll N = 2e5 + 123, inf = 1e9 + 9;
struct st_lazy
{

    vector<ll> t, lazy;
    ll n;

    st_lazy(ll n)
    {
        this->n = n;
        t.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    void push(ll nod, ll a, ll b)
    {
        if (lazy[nod] == 0)
            return;
        t[nod] += (b - a + 1) * lazy[nod];
        if (a != b)
        {
            lazy[2 * nod + 1] += lazy[nod];
            lazy[2 * nod + 2] += lazy[nod];
        }
        lazy[nod] = 0;
    }

    void update(ll nod, ll a, ll b, ll l, ll r, ll x)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return;
        if (l <= a && b <= r)
        {
            lazy[nod] += x;
            push(nod, a, b);
            return;
        }

        ll mid = (a + b) >> 1;
        update(2 * nod + 1, a, mid, l, min(r, mid), x);
        update(2 * nod + 2, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = (t[2 * nod + 1] + t[2 * nod + 2]);
    }

    ll query(ll nod, ll a, ll b, ll l, ll r)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return 0;

        if (l <= a && b <= r)
            return t[nod];

        ll mid = (a + b) >> 1;
        return (query(2 * nod + 1, a, mid, l, r) + query(2 * nod + 2, mid + 1, b, l, r));
    }
};

const ll M = 19;
st_lazy seg(N);

ll tme = 1, n;
vector<array<ll, 3>> g[N];
ll in[N], out[N], to[N], par[N][M], dep[N];
long long val[N], a[N];

void dfs(ll node, ll parent)
{
    in[node] = tme++;
    dep[node] = dep[parent] + 1;
    val[node] += val[parent];
    seg.update(0, 0, N - 1, in[node], in[node], val[node]);
    par[node][0] = parent;
    for (ll i = 1; i < M; ++i)
    {
        par[node][i] = par[par[node][i - 1]][i - 1];
    }
    for (auto u : g[node])
    {
        if (u[0] != parent)
        {
            val[u[0]] += u[1];
            to[u[2]] = u[0];
            a[u[0]] = u[1];
            dfs(u[0], node);
        }
    }
    out[node] = tme;
}

ll lca(ll u, ll v)
{
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    ll d = dep[u] - dep[v];
    for (ll i = M - 1; i >= 0; --i)
    {
        if (d >> i & 1)
        {
            u = par[u][i];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (ll i = M - 1; i >= 0; --i)
    {
        if (par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

long long dis(ll u, ll v)
{
    ll l = lca(u, v);
    ll x = seg.query(0, 0, N - 1, in[u], in[u]);
    ll y = seg.query(0, 0, N - 1, in[v], in[v]);
    ll z = 2 * seg.query(0, 0, N - 1, in[l], in[l]);
    return (x + y - z);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n - 1; ++i)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        g[x].push_back({y, w, i});
        g[y].push_back({x, w, i});
    }
    dfs(1, 0);
    ll q;
    cin >> q;
    while (q--)
    {
        ll t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            ll node = to[x];
            long long delta = y - a[node];
            seg.update(0, 0, N - 1, in[node], out[node] - 1, delta);
            a[node] = y;
        }
        else
        {
            cout << dis(x, y) << '\n';
        }
    }
    return 0;
}