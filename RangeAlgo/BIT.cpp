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

///////////////////////////
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
///////////////////////////
const ll N = 3e5 + 9;

template <class T>
struct BIT
{ // 1-indexed
    ll n;
    vector<T> t;
    BIT() {}
    BIT(ll _n)
    {
        n = _n;
        t.assign(n + 1, 0);
    }
    T query(ll i)
    {
        T ans = 0;
        for (; i >= 1; i -= (i & -i))
            ans += t[i];
        return ans;
    }
    void upd(ll i, T val)
    {
        if (i <= 0)
            return;
        for (; i <= n; i += (i & -i))
            t[i] += val;
    }
    void upd(ll l, ll r, T val)
    {
        upd(l, val);
        upd(r + 1, -val);
    }
    T query(ll l, ll r)
    {
        return query(r) - query(l - 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    cin >> tc;
    while (tc--)
    {
        ll n, m;
        cin >> n >> m;
        vector<pii> v(m);
        for (auto &a : v)
            cin >> a.first >> a.second;

        ll q;
        cin >> q;
        vector<ll> qry(q);
        for (ll i = 0; i < q; i++)
            cin >> qry[i];
        ll l = 1, r = q, res = -1;
        BIT<ll> fenw(n);
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            for (ll i = 0; i < mid; i++)
                fenw.upd(qry[i], 1);
            bool ok = false;
            // cout << mid << " sz\n";
            for (auto u : v)
            {
                ll p = fenw.query(u.first, u.second);
                ll q = u.second - u.first + 1;
                // cout << p << " " << q << " lol\n";
                if (p > q - p)
                {
                    ok = true;
                    break;
                }
            }
            for (ll i = 0; i < mid; i++)
                fenw.upd(qry[i], -1);
            if (ok)
                r = mid - 1, res = mid;
            else
                l = mid + 1;
        }
        cout << res;

        cout << "\n";
    }
    return 0;
}
// https://codeforces.com/contest/1843/problem/E
