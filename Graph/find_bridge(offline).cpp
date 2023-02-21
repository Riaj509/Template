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

// A bridge is defined as an edge which, when removed, makes the graph disconnected (or more precisely, increases the number of connected components in the graph).
const ll mx = 1e4;
ll n, m;
vector<ll> adj[mx];

vector<bool> visited;
vector<ll> tin, low;
set<pair<ll, ll>> st;
ll timer;

void bridge(ll u, ll v)
{
    st.insert({min(u, v), max(u, v)});
}

void dfs(ll v, ll p = -1)
{
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto to : adj[v])
    {
        if (to == p)
            continue;
        if (visited[to])
        {
            low[v] = min(low[v], tin[to]);
        }
        else
        {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                bridge(v, to);
        }
    }
}

void init()
{
    timer = 0;
    visited.assign(n + 1, false);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    st.clear();
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        cin >> n >> m;
        init();
        for (int i = 1; i <= m; i++)
        {
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
                dfs(i);
        }
        cout << "Caso #" << t << '\n';
        if (st.empty())
            cout << "Sin bloqueos\n";
        else
        {
            cout << st.size() << "\n";
            for (auto u : st)
                cout << u.first << " " << u.second << "\n";
        }

        // cout << "\n";
    }
    return 0;
} // https://www.spoj.com/problems/EC_P/