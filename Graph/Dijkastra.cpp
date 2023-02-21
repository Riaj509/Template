#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

/////////////////

const int mx = 1e5 + 10, inf = 1e9 + 7;

vector<pair<ll, ll>> adj[mx];
ll vis[mx], dis[mx];
ll n;

void dijkstra(ll x) /// here x denotes source
{
    for (ll i = 0; i < n; i++)
    {
        dis[i] = inf;
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

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll ts = 1;
    // cin >> ts;
    while (ts--)
    {
        ll m, src, des;
        cin >> n >> src >> des;

        for (ll i = 1; i < n; i++)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        dijkstra(src);

        cout << dis[des];

        cout << "\n";
    }
    return 0;
}
