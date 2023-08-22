//....................................<In the name of a1lah>...............................//

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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

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
        fa1tu(args);            \
    } while (0)

void fa1tu()
{
    cerr << endl;
}

template <typename T>
void fa1tu(T a[], ll n)
{
    for (ll i = 0; i < n; ++i)
        cerr << a[i] << ' ';
    cerr << endl;
}

template <typename T, typename... hello>
void fa1tu(T arg, const hello &...rest)
{
    cerr << arg << ' ';
    fa1tu(rest...);
}
//////////////////////////////-------->

bool isKthBitSet(ll n, ll k)
{
    if (n & (1 << (k - 1)))
        return true;
    return false;
}
bool poweroftwo(ll k) // domplexity O(1)
{
    return k && (!(k & (k - 1)));
}
bool powerofthree(ll n) // domplexity O(1)
{
    if (n <= 0)
        return false;
    return 1162261467 % n == 0;
}

////////powMod---cuxom//////
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
//////////////////////////////
namespace PollardRho
{
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int P = 1e6 + 9;
    ll seq[P];
    int primes[P], spf[P];
    inline ll add_mod(ll x, ll y, ll m)
    {
        return (x += y) < m ? x : x - m;
    }
    inline ll mul_mod(ll x, ll y, ll m)
    {
        ll res = x * y % m;
        return res;
        // ll res = x * y - (ll)((long double)x * y / m + 0.5) * m;
        // return res < 0 ? res + m : res;
    }
    inline ll pow_mod(ll x, ll n, ll m)
    {
        ll res = 1 % m;
        for (; n; n >>= 1)
        {
            if (n & 1)
                res = mul_mod(res, x, m);
            x = mul_mod(x, x, m);
        }
        return res;
    }
    // O(it * (logn)^3), it = number of rounds performed
    inline bool miller_rabin(ll n)
    {
        if (n <= 2 || (n & 1 ^ 1))
            return (n == 2);
        if (n < P)
            return spf[n] == n;
        ll c, d, s = 0, r = n - 1;
        for (; !(r & 1); r >>= 1, s++)
        {
        }
        // each iteration is a round
        for (int i = 0; primes[i] < n && primes[i] < 32; i++)
        {
            c = pow_mod(primes[i], r, n);
            for (int j = 0; j < s; j++)
            {
                d = mul_mod(c, c, n);
                if (d == 1 && c != 1 && c != (n - 1))
                    return false;
                c = d;
            }
            if (c != 1)
                return false;
        }
        return true;
    }
    void init()
    {
        int cnt = 0;
        for (int i = 2; i < P; i++)
        {
            if (!spf[i])
                primes[cnt++] = spf[i] = i;
            for (int j = 0, k; (k = i * primes[j]) < P; j++)
            {
                spf[k] = primes[j];
                if (spf[i] == spf[k])
                    break;
            }
        }
    }
    // returns O(n^(1/4))
    ll pollard_rho(ll n)
    {
        while (1)
        {
            ll x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
            ll *px = seq, *py = seq;
            while (1)
            {
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                *py++ = y = add_mod(mul_mod(y, y, n), c, n);
                if ((x = *px++) == y)
                    break;
                v = u;
                u = mul_mod(u, abs(y - x), n);
                if (!u)
                    return __gcd(v, n);
                if (++t == 32)
                {
                    t = 0;
                    if ((u = __gcd(u, n)) > 1 && u < n)
                        return u;
                }
            }
            if (t && (u = __gcd(u, n)) > 1 && u < n)
                return u;
        }
    }
    vector<ll> factorize(ll n)
    {
        if (n == 1)
            return vector<ll>();
        if (miller_rabin(n))
            return vector<ll>{n};
        vector<ll> v, w;
        while (n > 1 && n < P)
        {
            v.push_back(spf[n]);
            n /= spf[n];
        }
        if (n >= P)
        {
            ll x = pollard_rho(n);
            v = factorize(x);
            w = factorize(n / x);
            v.insert(v.end(), w.begin(), w.end());
        }
        return v;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    PollardRho::init();
    ll tc = 1,
       p = 0;
    cin >> tc;
    while (tc--)
    {
        ll a, b, k;
        cin >> a >> b >> k;
        if (k == 1)
        {
            if ((a % b == 0 || b % a == 0) && a != b)
                cout << "YES\n";
            else
                cout << "NO\n";
            continue;
        }
        auto x = PollardRho::factorize(a);
        auto y = PollardRho::factorize(b);
        if (x.size() + y.size() >= k)
            cout << "YES";
        else
            cout << "NO";

        cout << "\n";
    }
} // https://codeforces.com/contest/1538/problem/D