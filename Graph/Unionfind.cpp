#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const ll N = 3e5 + 9;

struct DSU
{
    vector<ll> par, rnk, sz;
    ll c;
    DSU(ll n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n)
    {
        for (ll i = 1; i <= n; ++i)
            par[i] = i;
    }
    ll find(ll i)
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(ll i, ll j)
    {
        return find(i) == find(j);
    }
    ll get_size(ll i)
    {
        return sz[find(i)];
    }
    ll count()
    {
        return c; // connected components
    }
    ll merge(ll i, ll j)
    {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j])
            swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        if (rnk[i] == rnk[j])
            rnk[j]++;
        return j;
    }
};
int main()
{

    ll n, m, cnt = 0;
    cin >> n >> m;
    DSU ds(n);
    vector<pair<ll, ll>> v(m);
    for (ll i = 0; i < m; i++)
    {
        cin >> v[i].first >> v[i].second;
    }
    sort(all(v));

    for (ll i = 0; i < m; i++)
    {
        ll x, y;
        x = v[i].first, y = v[i].second;
        if (ds.same(x, y))
            cnt++;
        else
            ds.merge(x, y);
    }
    cout << cnt << " " << ds.count() << "\n";
}