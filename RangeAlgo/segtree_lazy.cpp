#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const ll mx = 2e5 + 123, inf = 1e9 + 9;
ll v[mx], v1[mx];
struct st_lazy
{

    ll t[4 * mx];
    ll lazy[4 * mx]; // set by x
    st_lazy()
    {
        memset(t, 0, sizeof(t));
        memset(lazy, 0, sizeof(lazy));
    }
    void build(ll nod, ll a, ll b)
    {
        lazy[nod] = inf;

        if (a == b)
        {
            t[nod] = v[a];
            return;
        }
        ll mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = min(t[nod << 1], t[nod << 1 | 1]);
    }
    void push(ll nod, ll a, ll b)
    {
        if (lazy[nod] == inf)
            return;

        t[nod] = min(t[nod], lazy[nod]);
        if (a != b)
        {
            lazy[nod << 1] = min(lazy[nod << 1], lazy[nod]);
            lazy[nod << 1 | 1] = min(lazy[nod << 1 | 1], lazy[nod]);
        }
        lazy[nod] = inf;
    }

    void update(ll nod, ll a, ll b, ll l, ll r, ll x)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return;
        if (l <= a && b <= r)
        {
            lazy[nod] = x;
            push(nod, a, b);
            return;
        }

        ll mid = (a + b) >> 1;
        update(nod << 1, a, mid, l, min(r, mid), x);
        update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = min(t[nod << 1], t[nod << 1 | 1]);
    }

    ll query(ll nod, ll a, ll b, ll l, ll r)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return inf;

        if (l <= a && b <= r)
            return t[nod];

        ll mid = (a + b) >> 1;
        return min(query(nod << 1, a, mid, l, r), query(nod << 1 | 1, mid + 1, b, l, r));
    }
} seg;
