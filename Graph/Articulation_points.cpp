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

//////////////////////////////////////////////////
ll dx[4] = {0, 1, -1, 0};
ll dy[4] = {1, 0, 0, -1};
const int N = 3e5 + 9;
int n, m;
int T, low[N], dis[N], art[N];
vector<int> g[N];
void dfs(int u, int pre = 0)
{
    low[u] = dis[u] = ++T;
    int child = 0;
    for (auto v : g[u])
    {
        if (!dis[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dis[u] && pre != 0)
                art[u] = 1;
            ++child;
        }
        else if (v != pre)
            low[u] = min(low[u], dis[v]);
    }
    if (pre == 0 && child > 1)
        art[u] = 1;
}
void init()
{
    T = 0;
    for (int i = 0; i <= n; ++i)
        g[i].clear(), art[i] = 0, dis[i] = 0, low[i] = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    // for (int t = 1; t <= tc; t++)
    // {
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        init();
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans += art[i];
        cout << ans << '\n';
    }

    // cout << "\n";
    // }
    return 0;
} // https://www.spoj.com/problems/SUBMERGE/