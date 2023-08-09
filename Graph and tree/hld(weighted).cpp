//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (ll) x.size()
#define F first
#define S second
#define mem(a, b) memset(a, b, sizeof(a))
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()

//////////////////////////////////////////////////

/* edge as per weight*/
const ll N = 2e5 + 9, inf = 1e9 + 9;
ll baseArry[N], basePos[N], chainNO, chainHead[N], parent[N], level[N], chainInd[N], ptr, p[N][40], sz[N];
vector<pair<ll, ll>> g[N];
vector<array<ll, 4>> eg;
struct st_lazy
{

    ll t[4 * N];
    ll lazy[4 * N];
    st_lazy()
    {
        mem(t, 0);
        mem(lazy, 0);
    }
    void build(ll nod, ll a, ll b)
    {
        lazy[nod] = 0;

        if (a == b)
        {
            t[nod] = baseArry[a];
            return;
        }
        ll mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = max(t[nod << 1], t[nod << 1 | 1]);
    }
    void push(ll nod, ll a, ll b)
    {
        if (lazy[nod] == -inf)
            return;

        t[nod] = (t[nod] + lazy[nod]);
        if (a != b)
        {
            lazy[nod << 1] = (lazy[nod << 1] + lazy[nod]);
            lazy[nod << 1 | 1] = (lazy[nod << 1 | 1] + lazy[nod]);
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
        update(nod << 1, a, mid, l, min(r, mid), x);
        update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = max(t[nod << 1], t[nod << 1 | 1]);
    }

    ll query(ll nod, ll a, ll b, ll l, ll r)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return -inf;

        if (l <= a && b <= r)
            return t[nod];

        ll mid = (a + b) >> 1;
        return max(query(nod << 1, a, mid, l, r), query(nod << 1 | 1, mid + 1, b, l, r));
    }
} seg;

ll dfs(ll u, ll lev)
{
    ll ret = 1;
    level[u] = lev;
    for (auto v : g[u])
    {
        if (parent[u] != v.F)
        {
            parent[v.F] = u;
            ret += dfs(v.F, lev + 1);
        }
    }

    sz[u] = ret;
    return ret;
}

void HLD(ll u, ll cost, ll pU)
{
    if (chainHead[chainNO] == -1)
    {
        chainHead[chainNO] = u;
    }

    chainInd[u] = chainNO;
    basePos[u] = ++ptr;
    baseArry[ptr] = cost;

    ll m = -1, id = -1, c = -1;

    for (auto v : g[u])
    {
        if (v.F != pU)
        {
            if (sz[v.F] > m)
            {
                m = sz[v.F];
                id = v.F;
                c = v.S;
            }
        }
    }

    if (id != -1)
        HLD(id, c, u);

    for (auto v : g[u])
    {
        if (v.F != pU && v.F != id)
        {
            chainNO++;
            HLD(v.F, v.S, u);
        }
    }
}

void preprocess(ll n)
{
    for (ll i = 1; i <= n; i++)
        p[i][0] = parent[i];

    for (ll j = 1; (1 << j) <= n; j++)
    {
        for (ll i = 1; i <= n; i++)
        {
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
}

ll LCA(ll u, ll v)
{
    if (level[u] < level[v])
        swap(u, v);

    ll dist = level[u] - level[v];

    ll rise;
    while (dist > 0)
    {
        rise = log2(dist);
        u = p[u][rise];
        dist -= (1 << rise);
    }

    if (u == v)
        return u;

    for (ll i = 20; i >= 0; i--)
    {
        if (p[u][i] != p[v][i] && p[u][i] != -1)
        {
            u = p[u][i];
            v = p[v][i];
        }
    }

    return parent[u];
}

ll query_ask(ll u, ll v)
{
    if (u == v)
        return 0;
    ll chainU, chainV = chainInd[v];
    ll ans = 0;

    while (1)
    {
        chainU = chainInd[u];
        if (chainU == chainV)
        {
            ans = max(ans, seg.query(1, 1, ptr, basePos[v] + 1, basePos[u]));
            break;
        }

        ans = max(ans, seg.query(1, 1, ptr, basePos[chainHead[chainU]], basePos[u]));
        u = chainHead[chainU];
        u = parent[u];
    }

    return ans;
}

ll queryAsk(ll u, ll v)
{
    ll lca = LCA(u, v);
    return max(query_ask(u, lca), query_ask(v, lca));
}

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

void init(ll n)
{
    ptr = 0, chainNO = 1;
    mem(p, -1);
    mem(chainHead, -1);

    dfs(1, 0);
    HLD(1, 0, -1);
    preprocess(n);
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
            eg.push_back({wt[i], p[i], q[i], i});
        }
        sort(all(eg));
        ll ans = 0;
        vector<ll> used(m + 1, 0);
        dsu ds(n);
        for (auto a : eg)
        {
            ll x = a[1], y = a[2], cst = a[0], use = a[3];
            if (ds.same(x, y))
                continue;
            ds.merge(x, y);
            ans += cst;
            used[use] = 1;
            g[x].push_back({y, cst});
            g[y].push_back({x, cst});
        }
        init(n);
        seg.build(1, 1, ptr);
        for (ll i = 1; i <= m; i++)
        {
            if (used[i])
                cout << ans << "\n";
            else
                cout << ans + wt[i] - queryAsk(p[i], q[i]) << "\n";
        }

        cout << "\n";
    }
    return 0;
} // https://codeforces.com/contest/609/problem/E
