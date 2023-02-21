//....................................<In the name of Aintah>...............................//

//.................................<Bismiintahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (int)x.size()
#define mem(a) memset(a, 0, sizeof a)
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()

//////////////////////////////////////////////////

/* Node as per weight*/
const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;
struct st_lazy
{

    int t[4 * N];
    int lazy[4 * N];
    st_lazy()
    {
        memset(t, 0, sizeof(t));
        memset(lazy, 0, sizeof(lazy));
    }
    void build(int nod, int a, int b)
    {
        lazy[nod] = 0;

        if (a == b)
        {
            t[nod] = 0;
            return;
        }
        int mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = max(t[nod << 1], t[nod << 1 | 1]);
    }
    void push(int nod, int a, int b)
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

    void update(int nod, int a, int b, int l, int r, int x)
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

        int mid = (a + b) >> 1;
        update(nod << 1, a, mid, l, min(r, mid), x);
        update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = max(t[nod << 1], t[nod << 1 | 1]);
    }

    int query(int nod, int a, int b, int l, int r)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return -inf;

        if (l <= a && b <= r)
            return t[nod];

        int mid = (a + b) >> 1;
        return max(query(nod << 1, a, mid, l, r), query(nod << 1 | 1, mid + 1, b, l, r));
    }
} seg;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0)
{
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    if (p)
        g[u].erase(find(g[u].begin(), g[u].end(), p));
    for (auto &v : g[u])
        if (v != p)
        {
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]])
                swap(v, g[u][0]);
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
int T, head[N], st[N], en[N];
void dfs_hld(int u)
{
    st[u] = ++T;
    for (auto v : g[u])
    {
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v);
    }
    en[u] = T;
}
int n;
int query_up(int u, int v)
{
    int ans = -inf;
    while (head[u] != head[v])
    {
        ans = max(ans, seg.query(1, 1, n, st[head[u]], st[u]));
        u = par[head[u]][0];
    }
    ans = max(ans, seg.query(1, 1, n, st[v], st[u]));
    return ans;
}
int query(int u, int v)
{
    int l = lca(u, v);
    int ans = query_up(u, l);
    if (v != l)
        ans = max(ans, query_up(v, kth(v, dep[v] - dep[l] - 1)));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        cin >> n;
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
        head[1] = 1;
        dfs_hld(1);
        int q;
        cin >> q;
        seg.build(1, 1, n);
        while (q--)
        {
            string ty;
            int u, v;
            cin >> ty >> u >> v;
            if (ty == "add")
            {
                seg.update(1, 1, n, st[u], en[u], v);
            }
            else
            {
                cout << query(u, v) << '\n';
            }
        }
        // cout << "\n";
    }
    return 0;
} // https://www.hackerrank.com/challenges/subtrees-and-paths/submissions/code/314388024
