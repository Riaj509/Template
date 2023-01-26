#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const ll N = 2e5 + 9;
ll a[N];
struct sparsetable
{
    pair<ll, ll> t[N][18];
    void build(ll n)
    {
        for (ll i = 1; i <= n; ++i)
        {
            t[i][0] = {a[i], a[i]};
        }

        for (ll k = 1; (1 << k) <= n; ++k)
        {
            for (ll i = 1; i + (1 << k) - 1 <= n; ++i)
            {
                t[i][k].first = max(t[i][k - 1].first, t[i + (1 << (k - 1))][k - 1].first);
                t[i][k].second = min(t[i][k - 1].second, t[i + (1 << (k - 1))][k - 1].second);
            }
        }
    }

    ll query(ll l, ll r)
    {
        ll k = 31 - __builtin_clz(r - l + 1);
        return max(t[l][k].first, t[r - (1 << k) + 1][k].first);
    }

    ll query1(ll l, ll r)
    {
        ll k = 31 - __builtin_clz(r - l + 1);
        return min(t[l][k].second, t[r - (1 << k) + 1][k].second);
    }
} sp;