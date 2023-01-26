#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const ll mx = 1e3;
vector<ll> adj[mx];
ll vis[mx];
ll recvis[mx];
ll parent[mx];
ll ck = 0;

void dfs(int node)
{
    vis[node] = 1;
    recvis[node] = 1;

    for (auto u : adj[node])
    {
        if (!vis[u])
        {
            parent[u] = node;
            dfs(u);
        }
        else
        {
            if (recvis[u])
            {
                ck = 1;
                break;
            }
        }
    }
    recvis[node] = 0;
}
int main()
{
    ll n, m;
    cin >> n >> m;

    for (int i = 1; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool f = false;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            parent[i] = -1;
            ck = 0;
            dfs(i);
            if (ck == 1)
            {
                f = true;
                break;
            }
        }
    }
    (f) ? cout << "Cycle detected" : cout << "NO";
}
