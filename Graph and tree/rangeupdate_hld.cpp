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
const ll inf = 2e18;
const int mod = 998244353;
const int M = 200005;
int n;
/// Heavy Light Decomposition on Trees, 0 based indices
/// With RMQ support for nodes
/// Define the operation, default is +
/// x * NIL = x, NIL = 0 for addition/subtraction, 1 for multiplication, INF/-INF for min/max, etc
/// RMQ to add values on nodes, if required to set/replace values modify appropriately
/// Template from _Ash__ code :
#define NIL 0
#define MAX 200010
#define OPT(a, b) ((a) + (b))
#define jump(x) ((num[x] == 0) ? -1 : down[up[x]])
#define clr(x) memset(x, 0, sizeof(x));
namespace hld
{
    int r, n, id;
    vector<int> adj[MAX];
    int nodeval[MAX], lazy[4 * MAX], tree[4 * MAX];                            /// RMQ
    int parent[MAX], children[MAX], height[MAX], num[MAX], up[MAX], down[MAX]; /// HLD

    /// num[i] = 0 if the edge from i to parent[i] is not heavy, otherwise num[i] = unique id of the heavy edge
    /// down[i] = -1 if there is no heavy edge from i to it's children, otherwise down[i] = node number of the heavy child of i
    /// up[i] = i, if i is root, otherwise up[i] = node number of parent of i following only heavy up edges and one last light edge

    void dfs(int i, int p)
    {
        parent[i] = p, children[i] = 1;
        if (i != p)
            height[i] = height[p] + 1;

        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++)
        {
            x = adj[i][j];
            if (x != p)
            {
                dfs(x, i);
                children[i] += children[x];
            }
        }
    }

    /// build heavy light decomposition
    void build(int i, int p)
    { /// hash = 989687
        up[i] = i;
        if (num[i])
            up[i] = up[p];

        int j, x, h = -1, l = adj[i].size();
        for (j = 0; j < l; j++)
        {
            x = adj[i][j];
            if ((x != p) && ((children[x] << 1) >= children[i]))
                h = x;
        }

        if (h != -1)
        {
            num[h] = ++id;
            build(h, i);
        }
        for (j = 0, down[i] = h; j < l; j++)
        {
            x = adj[i][j];
            if ((x != p) && (x != h))
                build(x, i);
        }
    }

    void update_rmq(int idx, int a, int b, int l, int r, int x); /// RMQ update defined for build
    void build(int root)
    { /// hash = 397248
        r = root, id = 0, height[r] = 0;
        dfs(r, r);
        build(r, r);
        for (int i = 0; i < n; i++)
        {
            if (up[i] == i)
                up[i] = parent[i];
        }

        /// Builds RMQ
        clr(lazy);
        for (int i = 0; i < (MAX << 2); i++)
            tree[i] = NIL;
        for (int i = 0; i < n; i++)
        {
            if (num[i])
                update_rmq(1, 1, id, num[i], num[i], nodeval[i]);
        }
    }
    void build()
    {
        build(0); /// Root set to 0 by default!
    }

    int lca(int a, int b)
    {
        while (up[a] != up[b])
        {
            if (height[up[a]] > height[up[b]])
                a = up[a];
            else
                b = up[b];
        }

        if (a == b)
            return a;
        if (num[a] && num[b])
        {
            if (height[a] < height[b])
                return a;
            else
                return b;
        }
        return up[a];
    }

    void add_edge(int a, int b)
    {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void init(int nodes)
    {
        clr(num);
        n = nodes;
        for (int i = 0; i < MAX; i++)
            adj[i].clear();
        for (int i = 0; i < n; i++)
            nodeval[i] = 0;
    }

    /************** RMQ functions **************/

    /// Change lazy propagation accordingly
    /// Note lazy and updates set for adding values in node, update if set/replace operation
    inline void push(int idx, int a, int b)
    {
        int c = (a + b) >> 1, d = c + 1, p = idx << 1, q = p | 1;
        if (lazy[idx])
        {
            tree[idx] += (lazy[idx] * (b - a + 1)); /// Change lazy according to operation
            if (a != b)
                lazy[p] += lazy[idx], lazy[q] += lazy[idx]; /// Change lazy according to operation
            lazy[idx] = 0;
        }
    }

    /// Change query accordingly
    int query_rmq(int idx, int a, int b, int l, int r)
    { /// hash = 87775
        int c = (a + b) >> 1, d = c + 1, p = idx << 1, q = p | 1;

        push(idx, a, b);
        if (a == l && b == r)
            return tree[idx];
        else if (r <= c)
            return query_rmq(p, a, c, l, r);
        else if (l >= d)
            return query_rmq(q, d, b, l, r);
        else
            return OPT(query_rmq(p, a, c, l, c), query_rmq(q, d, b, d, r));
    }

    /// Change update accordingly
    void update_rmq(int idx, int a, int b, int l, int r, int x)
    { /// hash = 487503
        int p = (idx << 1), q = p + 1, c = (a + b) >> 1, d = c + 1;

        if (a == l && b == r)
            lazy[idx] += x; /// Change lazy according to operation, change here if set
        push(idx, a, b);
        if (a == l && b == r)
            return;

        if (r <= c)
        {
            push(q, d, b);
            update_rmq(p, a, c, l, r, x);
        }
        else if (l >= d)
        {
            push(p, a, c);
            update_rmq(q, d, b, l, r, x);
        }
        else
        {
            update_rmq(p, a, c, l, c, x);
            update_rmq(q, d, b, d, r, x);
        }

        tree[idx] = OPT(tree[p], tree[q]);
    }

    /************** HLD + RMQ **************/

    /// Sum of all nodes in the path from u to l, l must be an ancestor of u
    int query_tree(int u, int l)
    { /// hash = 486879
        int res = NIL;
        while (height[u] > height[l])
        {
            if (num[u])
            {
                int v = jump(u);
                if (height[v] <= height[l])
                    v = down[l];
                res = OPT(res, query_rmq(1, 1, id, num[v], num[u]));
                u = parent[v];
            }
            else
                res = OPT(nodeval[u], res), u = parent[u];
        }
        return res;
    }

    /// Sum of all nodes in the path from u to v
    int query(int u, int v)
    {
        int l = lca(u, v), res = NIL;
        res = OPT(res, query_tree(u, l));
        res = OPT(res, query_tree(v, l));
        if (!num[l])
            res = OPT(nodeval[l], res);
        else
            res = OPT(query_rmq(1, 1, id, num[l], num[l]), res);
        return res;
    }

    /// Add w to all nodes in the path from u to l, l must be an ancestor of u
    void update_tree(int u, int l, int w)
    { /// hash = 423845
        while (height[u] > height[l])
        {
            if (num[u])
            {
                int v = jump(u);
                if (height[v] <= height[l])
                    v = down[l];
                update_rmq(1, 1, id, num[v], num[u], w);
                u = parent[v];
            }
            else
                nodeval[u] = OPT(nodeval[u], w), u = parent[u]; /// Change here if set instead of add
        }
    }

    /// Add w to all nodes in the path from u to v
    void update(int u, int v, int w)
    {
        int l = lca(u, v);
        update_tree(u, l, w);
        update_tree(v, l, w);
        if (!num[l])
            nodeval[l] = OPT(nodeval[l], w); /// Change here if set instead of add
        else
            update_rmq(1, 1, id, num[l], num[l], w);
    }
}

vector<int> adj[M];
int a[M], st[M], en[M], tym = 0;

int bit[M + 2];

/// set a[idx]+=val;
void update(int idx, int val)
{
    while (idx < M)
    {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}
/// returns the prefix sum from 0 to idx
int qry(int idx)
{
    int ret = 0;
    while (idx > 0)
    {
        ret += bit[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

void dfs(int u, int p = -1)
{
    st[u] = ++tym;
    for (auto v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
    }
    en[u] = tym;
}

int rsum(int lft, int rgt)
{
    if (lft > rgt)
        return 0;
    int ret = qry(rgt);
    if (lft != 0)
        ret -= qry(lft - 1);
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    tym = 0;
    hld::init(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        hld::add_edge(u, v);
    }
    dfs(0);
    hld::build(0);
    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++)
        {
            cin >> a[i];
            a[i]--;
            hld::update(a[i], a[i], 1);
            update(st[a[i]], 1);
        }
        vector<int> col;
        for (int i = 1; i <= k; i++)
        {
            int u = st[a[i]], v = en[a[i]];
            if (rsum(u, v) == 1)
                col.push_back(a[i]);
        }
        bool f = true;
        if (col.size() >= 3)
            f = false;
        else if (col.size() >= 2)
        {
            int u = col[0], v = col[1];
            if (hld::query(u, v) != k)
                f = false;
        }
        if (f)
            cout << "YES\n";
        else
            cout << "NO\n";
        for (int i = 1; i <= k; i++)
        {
            hld::update(a[i], a[i], -1);
            update(st[a[i]], -1);
        }
    }

    return 0;
} // https://codeforces.com/contest/1702/problem/G2