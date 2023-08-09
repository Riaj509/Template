#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

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
