#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
const int mx = 2e6;
ll t[4 * mx];
ll lazy1[4 * mx];
ll lazy2[4 * mx];
struct st_lazy
{
    ll t[4 * mx];
    ll lazy1[4 * mx]; // increase by x
    ll lazy2[4 * mx]; // set by x
    st_lazy()
    {
        memset(t, 0, sizeof(t));
        memset(lazy1, 0, sizeof(lazy1));
        memset(lazy2, 0, sizeof(lazy2));
    }
    void build(vector<ll> &v, ll nod, ll a, ll b)
    {
        if (a == b)
            t[nod] = v[a];
        else
        {
            ll mid = (a + b) >> 1;
            build(v, nod << 1, a, mid);
            build(v, nod << 1 | 1, mid + 1, b);
            t[nod] = t[nod << 1] + t[nod << 1 | 1];
        }
    }
    void push(ll nod, ll a, ll b)
    {
        if (lazy2[nod])
        {
            t[nod] = (b - a + 1) * lazy2[nod];
            if (a != b)
            {
                lazy2[nod << 1] = lazy2[nod];
                lazy1[nod << 1] = 0;
                lazy2[nod << 1 | 1] = lazy2[nod];
                lazy1[nod << 1 | 1] = 0;
            }
            lazy2[nod] = 0;
        }
        if (lazy1[nod])
        {
            t[nod] += (b - a + 1) * lazy1[nod];
            if (a != b)
            {
                lazy1[nod << 1] += lazy1[nod];
                // lazy2[nod << 1] = 0;
                lazy1[nod << 1 | 1] += lazy1[nod];
                // lazy2[nod << 1 | 1] = 0;
            }
            lazy1[nod] = 0;
        }
    }

    void update(ll nod, ll a, ll b, ll l, ll r, ll x, ll ty)
    {
        push(nod, a, b);
        if (l > r)
            return;
        if (l == a && b == r)
        {
            if (ty == 1)
                lazy1[nod] += x;
            else
            {
                lazy2[nod] = x;
                lazy1[nod] = 0;
            }
            push(nod, a, b);
        }
        else
        {
            ll mid = (a + b) >> 1;
            update(nod << 1, a, mid, l, min(r, mid), x, ty);
            update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x, ty);
            t[nod] = (t[nod << 1] + t[nod << 1 | 1]);
        }
    }

    ll query(ll nod, ll a, ll b, ll l, ll r)
    {
        push(nod, a, b);
        if (l > r)
            return 0;

        if (l == a && b == r)
            return t[nod];

        ll mid = (a + b) >> 1;
        return (query(nod << 1, a, mid, l, min(r, mid)) + query(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r));
    }

} seg;
