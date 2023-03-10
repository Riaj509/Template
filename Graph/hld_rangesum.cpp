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

const int N = 500050;
const ll inf = 2e18;
/// query on change a node value and sum of the path u to v
///  For subtree update you just store start and end node in the subtree root
const int LG = 16;
int arr[N], total_chain, T, node[N], pos[N];
int par[N][LG + 1], son[N], chain_head[N], sz[N], dep[N], chain_no[N];
vector<int> g[N];
/// we can use ANY DATA STRUCTURE HERE AFTER building hld array
struct segtree
{
    int t[4 * N];
    void build(int n, int b, int e)
    {
        if (b == e)
        {
            t[n] = arr[node[b]];
            return;
        }
        int l = n * 2;
        int r = l + 1;
        int mid = (b + e) / 2;
        build(l, b, mid);
        build(r, mid + 1, e);
        t[n] = t[l] + t[r];
    }
    void upd(int n, int b, int e, int i, int x)
    {
        if (b > i || e < i)
            return;
        if (b == e && b == i)
        {
            t[n] = x;
            return;
        }
        int l = n * 2;
        int r = l + 1;
        int mid = (b + e) / 2;
        upd(l, b, mid, i, x);
        upd(r, mid + 1, e, i, x);
        t[n] = t[l] + t[r];
    }
    int query(int n, int b, int e, int i, int j)
    {
        if (b > j || e < i)
            return 0;
        if (b >= i && e <= j)
            return t[n];
        int l = n * 2;
        int r = l + 1;
        int mid = (b + e) / 2;
        int a = query(l, b, mid, i, j);
        int p = query(r, mid + 1, e, i, j);
        return a + p;
    }
} t;
void dfs(int u, int pre)
{
    dep[u] = dep[pre] + 1;
    int mx = -1;
    sz[u] = 1;
    par[u][0] = pre;
    for (int i = 1; i <= LG; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (auto v : g[u])
    {
        if (v == pre)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx)
            mx = sz[v], son[u] = v; /// for bigchild
    }
}
int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int k = LG; k >= 0; k--)
        if (dep[par[u][k]] >= dep[v])
            u = par[u][k];
    if (u == v)
        return u;
    for (int k = LG; k >= 0; k--)
        if (par[u][k] != par[v][k])
            u = par[u][k], v = par[v][k];
    return par[u][0];
}
int kth(int u, int k)
{
    assert(k >= 0);
    for (int i = 0; i <= LG; i++)
        if (k & (1 << i))
            u = par[u][i];
    return u;
}
int dist(int u, int v)
{
    int lc = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[lc];
}
/// kth node from u to v,0th node is u
int go(int u, int v, int k)
{
    int lc = lca(u, v);
    int d = dep[u] + dep[v] - 2 * dep[lc];
    assert(k <= d);
    if (dep[lc] + k <= dep[u])
        return kth(u, k);
    k -= dep[u] - dep[lc];
    return kth(v, dep[v] - dep[lc] - k);
}
void hld(int u, int pre)
{
    if (chain_head[total_chain] == -1)
        chain_head[total_chain] = u;
    pos[u] = ++T;
    node[T] = u;
    chain_no[u] = total_chain;
    if (son[u] == -1)
        return;
    hld(son[u], u);
    for (auto v : g[u])
    {
        if (v == pre || v == son[u])
            continue;
        total_chain++;
        hld(v, u);
    }
}
/// v must be an ancestor of u
///  lca(u,v) = v
int query_up(int u, int v)
{
    int ans = 0;
    int chain1 = chain_no[u];
    int chain2 = chain_no[v];
    int chd_u = chain_head[chain1];
    int chd_v = chain_head[chain2];
    while (chd_u != chd_v)
    {
        ans += t.query(1, 1, T, pos[chd_u], pos[u]); /// queries should be from low depth node to high depth node
        u = par[chd_u][0];
        chain1 = chain_no[u];
        chd_u = chain_head[chain1];
    }
    ans += t.query(1, 1, T, pos[v], pos[u]);
    return ans;
}
int query(int u, int v)
{
    int lc = lca(u, v);
    int ans = query_up(u, lc);
    if (v != lc)
        ans += query_up(v, kth(v, dep[v] - dep[lc] - 1));
    return ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int i, j, k, n, m, u, v, q, tt, w;
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> arr[i];
    for (i = 1; i < n; i++)
        cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    mem(son, -1);
    mem(chain_head, -1);
    dfs(1, 0);
    hld(1, 0);
    t.build(1, 1, T);
    cin >> q;
    while (q--)
    {
        cin >> tt;
        if (tt == 1)
        {
            cin >> u >> w;
            arr[u] = w;
            t.upd(1, 1, T, pos[u], w);
        }
        else
        {
            cin >> u >> v;
            cout << query(u, v) << endl;
        }
    }
    return 0;
}