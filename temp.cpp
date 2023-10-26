//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef vector<pair<ll, ll>> vli;
typedef double dl;
typedef map<ll, ll> mp;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define MOD 1000000007

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fined, ios::floatfield);
//////////////////////////////Debug part////////////////////////////////////
template <typename F, typename S>
void faltu(pair<F, S> p) { cerr << "(" << p.first << ", " << p.second << ")"; }

template <typename T>
void faltu(vector<T> v)
{
    cerr << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            cerr << ", ";
        cerr << *it;
    }
    cerr << "}";
}

template <typename T>
void faltu(set<T> v)
{
    cerr << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            cerr << ", ";
        cerr << *it;
    }
    cerr << "}";
}

template <typename T>
void faltu(multiset<T> v)
{
    cerr << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            cerr << ", ";
        cerr << *it;
    }
    cerr << "}";
}

template <typename F, typename S>
void faltu(map<F, S> v)
{
    cerr << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            cerr << ", ";
        cerr << it->first << " = " << it->second;
    }
    cerr << "]";
}

template <typename F, typename S>
void faltu(unordered_map<F, S> v)
{
    cerr << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            cerr << ", ";
        cerr << it->first << " = " << it->second;
    }
    cerr << "]";
}

template <typename T>
void faltu(stack<T> v)
{
    cerr << "{";
    while (!v.empty())
    {
        cerr << v.top();
        v.pop();
        if (!v.empty())
            cerr << ", ";
    }
    cerr << "}";
}

template <typename T>
void faltu(queue<T> v)
{
    cerr << "{";
    while (!v.empty())
    {
        cerr << v.front();
        v.pop();
        if (!v.empty())
            cerr << ", ";
    }
    cerr << "}";
}

template <typename T>
void faltu(priority_queue<T> v)
{
    cerr << "{";
    while (!v.empty())
    {
        cerr << v.front();
        v.pop();
        if (!v.empty())
            cerr << ", ";
    }
    cerr << "}";
}

#define dbg(args...)            \
    do                          \
    {                           \
        cerr << #args << " : "; \
        faltu(args);            \
    } while (0)

void faltu() { cerr << endl; }

template <typename T>
void faltu(T a[], int n)
{
    for (int i = 0; i < n; ++i)
        cerr << a[i] << ' ';
    cerr << endl;
}

template <typename T, typename... hello>
void faltu(T arg, const hello &...rest)
{
    cerr << arg << ' ';
    faltu(rest...);
}

///////////bit-manipulation///////////////
#define MSB(mask) 63 - __builtin_clzll(mask)
#define LSB(mask) __builtin_ctzll(mask)
#define ONE(mask) __builtin_popcountll(mask)
#define CHECK(mask, bit) (mask & (1LL << bit))
#define ON(mask, bit) (mask | (1LL << bit))
#define OFF(mask, bit) (mask & ~(1LL << bit))
#define CHANGE(mask, bit) (mask ^ (1LL << bit))
////////powMod---custom//////
ll power(ll x, ll y, ll p)
{
    ll res = 1;

    x = x % p;

    while (y > 0)
    {

        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    while (tc--)
    {
    }

    return 0;
}
