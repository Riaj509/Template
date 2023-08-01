//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef double dl;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);

//////////////////////////////-------->
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
string s;
ll sz;
ll dp[20][2][5];

ll solve(ll pos, ll tig, ll cnt)
{
    if (pos >= sz)
    {
        return cnt <= 3;
    }
    if (cnt > 3)
        return 0;
    if (dp[pos][tig][cnt] != -1)
        return dp[pos][tig][cnt];

    ll ans = 0;
    ll lim;
    if (tig)
        lim = s[pos] - '0';
    else
        lim = 9;
    for (ll cur = 0; cur <= lim; ++cur)
    {
        ll tig1 = tig;
        if (tig && cur < lim)
            tig1 = 0;
        ll ncnt = cnt + (cur > 0);
        ans += solve(pos + 1, tig1, ncnt);
    }
    return dp[pos][tig][cnt] = ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        ll l, r;
        cin >> l >> r;
        --l;
        s = to_string(r);
        sz = s.size();
        mem(dp, -1);
        ll res = solve(0, 1, 0);
        mem(dp, -1);
        s = to_string(l);
        sz = s.size();
        ll res1 = solve(0, 1, 0);
        cout << res - res1;
        cout << "\n";
    }

    return 0;
} // https://codeforces.com/contest/1036/problem/C