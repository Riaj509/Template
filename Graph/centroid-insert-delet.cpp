//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define eps 10e-6;

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);

//////////////////////////////-------->

// You are given a tree(an acyclic undirected connected graph) with N nodes.The tree nodes are numbered from 1 to N.We define dist(a, b) as the number of edges on the path from node a to node b.

// Each node has a color, white or black. All the nodes are black initially.

// We will ask you to perform some instructions of the following form:

// 0 i : change the color of i-th node(from black to white, or from white to black).
// 1 v : ask for the minimum dist(u, v), node u must be white(u can be equal to v). Obviously, as long as node v is white, the result will always be 0.
const int N = 2e5 + 5;
const int maxN = 1e6 + 6;
const ll Mod = 1e9 + 7;
const int inf = 2e9;
const ll Inf = 1e18;

int dep[N], par[N], sub[N], P[N][18], ans[N], len;
bool mark[N];
multiset<pair<int, int>> st[N];
bool white[N];
struct Centroid_Decomposition
{
    vector<vector<int>> g;
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
        g.assign(n + 1, vector<int>());
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

    void add(int x, int y)
    {
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int solve(int x)
    {
        multiset<pair<int, int>> &q = st[x];

        while (!q.empty())
        {
            pair<int, int> cur = *q.begin();
            if (!white[cur.second])
                q.erase(q.begin());
            else
                return cur.first;
        }
        return inf;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Centroid_Decomposition tree;
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        int n, root = 1, m;
        cin >> n;
        tree.init(n);
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            tree.add(x, y);
        }
        tree.dfs(root);
        tree.decompose(root, 0);
        tree.modify(root);
        // vector<int> res(n + 1, 1);
        // res[0] = inf;
        vector<int> opr(n + 1, 0);
        cin >> m;
        for (int i = 1; i <= m; ++i)
        {
            int t, x;
            cin >> t >> x;
            if (t == 0)
            {
                white[x] = !white[x];
                if (white[x])
                {
                    int p = x;
                    while (p)
                    {
                        st[p].insert({tree.dist(p, x), x});
                        p = par[p];
                    }
                }
            }
            else
            {
                int res = inf;
                int p = x;
                while (p)
                {
                    res = min(res, tree.dist(x, p) + tree.solve(p));
                    p = par[p];
                }
                cout << (res == inf ? -1 : res);
                cout << "\n";
            }
        }

        // cout << "\n";
    }
    return 0;
} // https://www.spoj.com/problems/QTREE5/
