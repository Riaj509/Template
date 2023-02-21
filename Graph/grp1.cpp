/// dijkastra ////////
void dijkstra(ll x) /// here x denotes source
{
    for (ll i = 0; i < n; i++)
    {
        dis[i] = INF;
    }
    priority_queue<pair<ll, ll>> q; //(curr node,distance)
    dis[x] = 0;
    q.push({x, 0});

    while (!q.empty())
    {
        ll v = q.top().first; // contain current node
        q.pop();
        if (vis[v] == 0)
        { // not visited
            vis[v] = 1;
            for (auto u : adj[v])
            {
                ll a = u.first;  // a = adj.node
                ll b = u.second; // b = adj.distance
                if (dis[v] + b < dis[a])
                {
                    dis[a] = dis[v] + b;
                    q.push({a, -dis[a]}); // push neg distance for min possible in next node
                }
            }
        }
    }
}
#include <bits/stdc++.h>

using namespace std;

const ll mx = 100;
vector<ll> adj[mx];
ll subtr_long_path[mx];
ll farthest_node[mx];

void dfs(ll u, ll p)
{
    farthest_node[u] = u;
    subtr_long_path[u] = 0;
    for (auto v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
        if (subtr_long_path[u] < subtr_long_path[v] + 1)
        {
            subtr_long_path[u] = subtr_long_path[v] + 1;
            farthest_node[u] = farthest_node[v];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll ts = 1;
    // cin >> ts;
    while (ts--)
    {
        ll n, m;
        cin >> n;

        for (ll i = 1; i < n; i++)
        {
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, -1);
        ll one_end = farthest_node[1];
        dfs(one_end, -1);
        ll other_end = farthest_node[one_end];
        cout << subtr_long_path[one_end];

        cout << "\n";
    }
    return 0;
}
