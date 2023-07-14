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
const ll N = 1e5 + 10;
ll v[N];
struct Node
{
    ll inv = 0;
    vector<ll> frq = vector<ll>(41, 0);
    Node()
    {
        inv = 0;
        for (int i = 1; i <= 40; i++)
            frq[i] = 0;
    }
    Node(ll x)
    {
        inv = 0;
        for (int i = 1; i <= 40; i++)
            frq[i] = 0;
        frq[x] = 1;
    }
};

struct segtree
{
    vector<Node> t;
    Node normal = Node();
    segtree()
    {
        t.assign(4 * N, normal);
    }
    Node combine(Node &a, Node &b)
    {
        Node cur;
        cur.inv = a.inv + b.inv;
        for (int i = 1; i <= 40; i++)
            cur.frq[i] = a.frq[i] + b.frq[i];

        for (int i = 2; i <= 40; i++)
        {
            for (int j = 1; j < i; ++j)
            {
                cur.inv += 1LL * a.frq[i] * b.frq[j];
            }
        }
        return cur;
    }

    void build(ll nod, ll a, ll b)
    {
        if (a == b)
        {
            t[nod] = Node(v[a]);
            return;
        }
        ll mid = (a + b) >> 1;
        build(nod << 1, a, mid);
        build(nod << 1 | 1, mid + 1, b);
        t[nod] = combine(t[nod << 1], t[nod << 1 | 1]);
    }
    void update(ll nod, ll a, ll b, ll l, ll r, ll x)
    {
        if (r < a || b < l)
            return;
        if (l <= a && b <= r)
        {
            t[nod] = Node(x);
            return;
        }
        ll mid = (a + b) >> 1;
        update(nod << 1, a, mid, l, min(r, mid), x);
        update(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r, x);
        t[nod] = combine(t[nod << 1], t[nod << 1 | 1]);
    }

    Node query(ll nod, ll a, ll b, ll l, ll r)
    {
        if (r < a || b < l)
        {
            return normal;
        }
        if (l <= a && b <= r)
            return t[nod];
        ll mid = (a + b) >> 1;
        Node lft, ri, res;
        lft = query(nod << 1, a, mid, l, min(r, mid));
        ri = query(nod << 1 | 1, mid + 1, b, max(l, mid + 1), r);
        res = combine(lft, ri);
        return res;
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
        ll n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
            cin >> v[i];
        seg.build(1, 1, n);
        while (q--)
        {
            int t;
            cin >> t;
            if (t == 1)
            {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(1, 1, n, l, r).inv << "\n";
            }
            else
            {
                ll idx, x;
                cin >> idx >> x;
                seg.update(1, 1, n, idx, idx, x);
            }
        }

        cout << "\n";
    }
} // https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/C