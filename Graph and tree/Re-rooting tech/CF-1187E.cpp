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
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define MOD 1000000007

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);

//////////////////////////////-------->
const int N = 2e5 + 10;
vector<int> g[N];
ll sz[N], score[N], ans;

void dfs(int u, int par)
{
    sz[u] = 1;
    for (auto v : g[u])
    {
        if (v == par)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
        score[u] += score[v];
    }
    score[u] += sz[u];
}

void dfs_up(int u, int par)
{
    ans = max(ans, score[u]);
    for (auto v : g[u])
    {
        if (v == par)
            continue;
        // re-root part
        score[u] -= score[v];
        score[u] -= sz[u];
        sz[u] -= sz[v];
        score[u] += sz[u];

        score[v] -= sz[v];
        sz[v] += sz[u];
        score[v] += sz[v];
        score[v] += score[u];

        dfs_up(v, u);
        // rollback-part

        score[v] -= score[u];
        score[v] -= sz[v];
        sz[v] -= sz[u];
        score[v] += sz[v];

        score[u] -= sz[u];
        sz[u] += sz[v];
        score[u] += sz[u];
        score[u] += score[v];
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, -1);
        dfs_up(1, -1);
        cout << ans;
        ans = 0;

        cout << "\n";
    }

    return 0;
}