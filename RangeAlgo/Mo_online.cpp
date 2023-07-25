#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll N = 1e5 + 5;
const ll Q = 1e5 + 5;
ll S;

struct query
{
    ll l, r, t, i;
    bool operator<(const query &o) const
    {
        if (l / S != o.l / S)
            return l < o.l;
        if (r / S != o.r / S)
            return r < o.r;
        return t < o.t;
    }
} q[Q];
struct updt
{
    ll i, nxt, prv;
} u[Q];

ll a[N], au[N];
ll ml = 0, mr = -1, t = 0;
long long re[Q], cur = 0;
unordered_map<ll, ll> cnt;
void add(ll i)
{
    ll x = a[i];
    auto it = cnt.find(x);
    if (it->second == 0 and x % 3 == 0)
        cur += x;
    ++(it->second);
}
void del(ll i)
{
    ll x = a[i];
    auto it = cnt.find(x);
    if (it->second == 1 and x % 3 == 0)
        cur -= x;
    --(it->second);
}
void updo(ll i)
{
    ll j = u[i].i, nxt = u[i].nxt;
    if (j >= ml and j <= mr)
        del(j);
    a[j] = nxt;
    if (j >= ml and j <= mr)
        add(j);
}
void undo(ll i)
{
    ll j = u[i].i, prv = u[i].prv;
    if (j >= ml and j <= mr)
        del(j);
    a[j] = prv;
    if (j >= ml and j <= mr)
        add(j);
}
int main()
{
    ll n, m, c;
    cin >> n >> m;
    S = n / cbrt(n);

    for (ll i = 0; i < n; ++i)
    {
        cin >> a[i];
        cnt[a[i]];
        au[i] = a[i];
    }
    ll su = 0, sq = 0, l, r;
    for (ll i = 0; i < m; ++i)
    {
        cin >> c >> l >> r;
        if (c == 1)
        {
            --l, --r;
            q[sq] = {l, r, su, sq};
            ++sq;
        }
        else
        {
            --l;
            cnt[r];
            u[su++] = {l, r, au[l]};
            au[l] = r;
        }
    }
    sort(q, q + sq);
    for (ll j = 0; j < sq; ++j)
    {
        ll l = q[j].l, r = q[j].r, qt = q[j].t, i = q[j].i;
        while (t < qt)
            updo(t++);
        while (t > qt)
            undo(--t);
        while (ml < l)
            del(ml++);
        while (ml > l)
            add(--ml);
        while (mr < r)
            add(++mr);
        while (mr > r)
            del(mr--);
        re[i] = cur;
    }
    for (ll i = 0; i < sq; i++)
        cout << re[i] << "\n";

    return 0;
} // https://toph.co/p/a-unique-array