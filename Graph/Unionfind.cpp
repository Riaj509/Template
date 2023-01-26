#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const int mxn = 1e5;
struct DSU
{
    int parent[mxn];
    int sz[mxn];

    void init(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            sz[i] = 1;
        }
    }
    int findrep(int u)
    {
        return parent[u] == u ? u : parent[u] = findrep(parent[u]);
    }
    void unite(int u, int v)
    {
        u = findrep(u);
        v = findrep(v);
        if (u == v)
            return;

        if (sz[u] > sz[v])
            swap(u, v);
        parent[u] = v;
        sz[v] += sz[u];
    }

} dsu;

int main()
{

    ll n;
    cin >> n;
    dsu.init(n);
}