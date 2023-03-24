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
#define sz(x) (int)x.size()
#define mem(a) memset(a, 0, sizeof a)
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
///////////////////////////////
struct Seg
{
    vector<long long> st, lazy;
    int n;

    Seg(int n)
    {
        this->n = n;
        st.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    long long query(int start, int end, int l, int r, int node)
    {
        if (lazy[node])
        {
            st[node] += (end - start + 1) * lazy[node];
            if (start != end)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (l > end or r < start)
        {
            return 0;
        }

        if (l <= start and r >= end)
        {
            return st[node];
        }

        int mid = (start + end) / 2;

        long long q1 = query(start, mid, l, r, node * 2 + 1);
        long long q2 = query(mid + 1, end, l, r, node * 2 + 2);

        return q1 + q2;
    }

    long long query(int l, int r)
    {
        return query(0, n - 1, l, r, 0);
    }

    void update(int start, int end, int node, int l, int r, long long val)
    {
        if (lazy[node] != 0)
        {
            st[node] += lazy[node] * (end - start + 1);
            if (start != end)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > r || end < l)
        {
            return;
        }
        if (start >= l && end <= r)
        {
            st[node] += val * (end - start + 1);
            if (start != end)
            {
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        int mid = (start + end) / 2;
        update(start, mid, 2 * node + 1, l, r, val);
        update(mid + 1, end, 2 * node + 2, l, r, val);
        st[node] = st[node * 2 + 1] + st[node * 2 + 2];
    }

    void update(int l, int r, long long x)
    {
        update(0, n - 1, 0, l, r, x);
    }
};

const int N = 2e5 + 15, M = 19;

Seg ds(N);

int tme = 1;
vector<array<int, 3>> g[N];
int in[N], out[N], to[N], par[N][M], dep[N];
long long val[N], a[N];

void dfs(int node, int parent)
{
    in[node] = tme++;
    dep[node] = dep[parent] + 1;
    val[node] += val[parent];
    ds.update(in[node], in[node], val[node]);
    par[node][0] = parent;
    for (int i = 1; i < M; ++i)
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

int lca(int u, int v)
{
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    int d = dep[u] - dep[v];
    for (int i = M - 1; i >= 0; --i)
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
    for (int i = M - 1; i >= 0; --i)
    {
        if (par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

long long dis(int u, int v)
{
    int l = lca(u, v);
    return ds.query(in[u], in[u]) + ds.query(in[v], in[v]) - 2 * ds.query(in[l], in[l]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; ++i)
    {
        int x, y, w;
        cin >> x >> y >> w;
        g[x].push_back({y, w, i});
        g[y].push_back({x, w, i});
    }
    dfs(1, 0);
    int q;
    cin >> q;
    while (q--)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            int node = to[x];
            long long delta = y - a[node];
            ds.update(in[node], out[node] - 1, delta);
            a[node] = y;
        }
        else
        {
            cout << dis(x, y) << '\n';
        }
    }
    return 0;
}