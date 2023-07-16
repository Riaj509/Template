//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef double dl;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
///////////////////debug-part////////////
template <typename F, typename S>
ostream &operator<<(ostream &os, const pair<F, S> &p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}
template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}
template <typename F, typename S>
ostream &operator<<(ostream &os, const map<F, S> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << it->first << " = " << it->second;
    }
    return os << "]";
}
#define dbg(args...)            \
    do                          \
    {                           \
        cerr << #args << " : "; \
        faltu(args);            \
    } while (0)

void faltu()
{
    cerr << endl;
}
template <typename T>
void faltu(T a[], ll n)
{
    for (ll i = 0; i < n; ++i)
        cerr << a[i] << ' ';
    cerr << endl;
}
template <typename T, typename... hello>
void faltu(T arg, const hello &...rest)
{
    cerr << arg << ' ';
    faltu(rest...);
}
//////////////////////////////////////
const ll mx = 2e5 + 123, inf = 1e9 + 9;
ll v[mx];
ll n;
struct Node
{
    ll mxsum, psum, sufsum, sum;
    Node() { mxsum = psum = sufsum = sum = 0; }
};

struct segtree
{
    vector<Node> t;
    vector<Node> lazy;
    Node ntrl;
    segtree()
    {
        t.resize(4 * mx + 1);
        lazy.resize(4 * mx + 1);
    }

    Node merge(Node &a, Node &b)
    {
        Node cur;
        cur.sum = a.sum + b.sum;
        cur.psum = max(a.psum, a.sum + b.psum);
        cur.sufsum = max(b.sufsum, b.sum + a.sufsum);
        cur.mxsum = max(a.mxsum, max(b.mxsum, a.sufsum + b.psum));
        return cur;
    }
    void push(ll nod, ll a, ll b)
    {
        if (lazy[nod].sum == INT_MAX)
            return;
        ll x = (b - a + 1) * (lazy[nod].sum);
        t[nod].sum = t[nod].mxsum = t[nod].psum = t[nod].sufsum = x;
        if (a != b)
        {
            lazy[nod << 1].sum = lazy[nod].sum;
            lazy[nod << 1 | 1].sum = lazy[nod].sum;
        }
        lazy[nod].sum = INT_MAX;
    }
    void build(ll nod, ll a, ll b)
    {
        lazy[nod].sum = INT_MAX;
        if (a == b)
        {
            t[nod].mxsum = t[nod].psum = t[nod].sufsum = t[nod].sum = 0;
            return;
        }
        ll mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = merge(t[nod << 1], t[nod << 1 | 1]);
    }
    void upd(ll nod, ll a, ll b, ll l, ll r, ll x)
    {
        push(nod, a, b);
        if (r < a || b < l)
            return;
        if (l <= a && b <= r)
        {
            lazy[nod].mxsum = lazy[nod].psum = lazy[nod].sufsum = lazy[nod].sum = x;
            push(nod, a, b);
            return;
        }
        ll mid = (a + b) >> 1;
        upd(nod << 1, a, mid, l, min(mid, r), x);
        upd(nod << 1 | 1, mid + 1, b, max(mid + 1, l), r, x);
        t[nod] = merge(t[nod << 1], t[nod << 1 | 1]);
    }

} seg;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--)
    {
        ll q;
        cin >> n >> q;
        seg.build(1, 1, n);
        while (q--)
        {
            ll t, l, r, x;
            cin >> l >> r >> x;
            seg.upd(1, 1, n, l + 1, r, x);
            cout << max(0LL, seg.t[1].mxsum) << "\n";
        }

        cout << "\n";
    }
}