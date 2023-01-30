#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int N = 2e5 + 5;
const int maxN = 1e6 + 6;
const ll Mod = 1e9 + 7;
const int inf = 2e9;
const ll Inf = 1e18;

#define Int Int()
#define Long Long()
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
#define mem(a) memset(a, 0, sizeof a)
#define memn(a) memset(a, -1, sizeof a)

int dep[N], par[N], sub[N], P[N][18], ans[N], len;
vector<vector<int>> g;
bool mark[N];

void dfs(int s, int p = 0)
{
    dep[s] = 1 + dep[p];
    P[s][0] = p;
    for (int i = 1; i < 18; ++i)
    {
        P[s][i] = P[P[s][i - 1]][i - 1];
    }
    for (int i : g[s])
    {
        if (i == p)
            continue;
        dfs(i, s);
    }
}

int LCA(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 17; i >= 0; --i)
    {
        if (d & (1 << i))
        {
            a = P[a][i];
        }
    }
    if (a == b)
        return a;
    for (int i = 17; i >= 0; --i)
    {
        if (P[a][i] != P[b][i])
        {
            a = P[a][i], b = P[b][i];
        }
    }
    return P[a][0];
}

int dist(int a, int b)
{
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}

void ComputeSize(int s, int p)
{
    sub[s] = 1;
    ++len;
    for (int i : g[s])
    {
        if (i == p or mark[i])
            continue;
        ComputeSize(i, s);
        sub[s] += sub[i];
    }
}

int getCentroid(int s, int p)
{
    for (int i : g[s])
    {
        if (i != p and !mark[i] and sub[i] > len / 2)
            return getCentroid(i, s);
    }
    return s;
}

void decompose(int s, int p)
{
    len = 0;
    ComputeSize(s, s);
    int centroid = getCentroid(s, s);
    par[centroid] = p;
    mark[centroid] = 1;
    for (int i : g[centroid])
    {
        if (!mark[i])
            decompose(i, centroid);
    }
}

void modify(int s)
{
    int p = s;
    while (p)
    {
        ans[p] = min(ans[p], dist(s, p));
        p = par[p];
    }
}

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= 17; ++j)
            P[i][j] = 0;
        dep[i] = 0;
        ans[i] = inf;
        par[i] = 0;
        mark[i] = 0;
    }
}

int query(int s)
{
    int res = inf;
    int p = s;
    while (p)
    {
        res = min(res, ans[p] + dist(s, p));
        p = par[p];
    }
    return res;
}

int main()
{
    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        int n, root;
        cin >> n >> root;
        g.assign(n + 1, vector<int>());
        vector<int> q(n);
        for (int i = 1; i < n; ++i)
            cin >> q[i];
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs(root);
        decompose(root, 0);
        fill(ans, ans + n + 1, inf);
        modify(root);
        vector<int> res(n + 1, 1);
        res[0] = inf;
        for (int i = 1; i < n; ++i)
        {
            res[i] = min(res[i - 1], query(q[i]));
            if (res[i] == 1)
                break;
            modify(q[i]);
        }
        for (int i = 1; i < n; ++i)
            cout << res[i] << " \n"[i == n - 1];
    }
}