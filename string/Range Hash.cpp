#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
///////single hash/////
const ll HASH = 257, MOD = 1e9 + 7;

int N, Q;
ll powH[200005] = {1};

namespace forward_hash
{
    ll T[400005];

    void update(int i, ll v)
    {
        for (T[i += N] = v; i > 1; i >>= 1)
            T[i >> 1] = (T[i] + T[i ^ 1]) % MOD;
    }

    ll query(int l, int r)
    {
        ll res = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = (res + T[l++]) % MOD;
            if (r & 1)
                res = (res + T[--r]) % MOD;
        }
        return res;
    }
}

namespace backward_hash
{
    ll T[400005];

    void update(int i, ll v)
    {
        for (T[i += N] = v; i > 1; i >>= 1)
            T[i >> 1] = (T[i] + T[i ^ 1]) % MOD;
    }

    ll query(int l, int r)
    {
        ll res = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = (res + T[l++]) % MOD;
            if (r & 1)
                res = (res + T[--r]) % MOD;
        }
        return res;
    }
}

int main()
{
    cin >> N >> Q;
    for (int i = 1; i < N; i++)
    {
        powH[i] = (powH[i - 1] * HASH) % MOD;
        // cout << powH[i] << " \n"[i == N - 1];
    }
    for (int i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        forward_hash::update(i, powH[i] * (ll)c % MOD);
        backward_hash::update(i, powH[N - i - 1] * (ll)c % MOD);
    }

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int k;
            char c;
            cin >> k >> c;
            k--;
            forward_hash::update(k, powH[k] * (ll)c % MOD);
            backward_hash::update(k, powH[N - k - 1] * (ll)c % MOD);
        }
        else if (t == 2)
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll forward = forward_hash::query(l, r);
            forward = (forward * powH[N - 1 - r]) % MOD;
            ll backward = backward_hash::query(l, r);
            backward = (backward * powH[l]) % MOD;
            if (forward == backward)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}

///////////Double-Hash///////
const int N = 2e5 + 9;

int power(long long n, long long k, const int mod)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (long long)ans * n % mod;
        n = (long long)n * n % mod;
        k >>= 1;
    }
    return ans;
}

using T = array<int, 2>;
const T MOD = {127657753, 987654319};
const T p = {137, 277};

T operator+(T a, int x) { return {(a[0] + x) % MOD[0], (a[1] + x) % MOD[1]}; }
T operator-(T a, int x) { return {(a[0] - x + MOD[0]) % MOD[0], (a[1] - x + MOD[1]) % MOD[1]}; }
T operator*(T a, int x) { return {(int)((long long)a[0] * x % MOD[0]), (int)((long long)a[1] * x % MOD[1])}; }
T operator+(T a, T x) { return {(a[0] + x[0]) % MOD[0], (a[1] + x[1]) % MOD[1]}; }
T operator-(T a, T x) { return {(a[0] - x[0] + MOD[0]) % MOD[0], (a[1] - x[1] + MOD[1]) % MOD[1]}; }
T operator*(T a, T x) { return {(int)((long long)a[0] * x[0] % MOD[0]), (int)((long long)a[1] * x[1] % MOD[1])}; }
ostream &operator<<(ostream &os, T hash) { return os << "(" << hash[0] << ", " << hash[1] << ")"; }

T pw[N], ipw[N];
void prec()
{
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i] = pw[i - 1] * p;
    }
    ipw[0] = {1, 1};
    T ip = {power(p[0], MOD[0] - 2, MOD[0]), power(p[1], MOD[1] - 2, MOD[1])};
    for (int i = 1; i < N; i++)
    {
        ipw[i] = ipw[i - 1] * ip;
    }
}
struct Hashing
{
    int n;
    string s;              // 1 - indexed
    vector<array<T, 2>> t; // (normal, rev) hash
    array<T, 2> merge(array<T, 2> l, array<T, 2> r)
    {
        l[0] = l[0] + r[0];
        l[1] = l[1] + r[1];
        return l;
    }
    void build(int node, int b, int e)
    {
        if (b == e)
        {
            t[node][0] = pw[b] * s[b];
            t[node][1] = pw[n - b + 1] * s[b];
            return;
        }
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        build(l, b, mid);
        build(r, mid + 1, e);
        t[node] = merge(t[l], t[r]);
    }
    void upd(int node, int b, int e, int i, char x)
    {
        if (b > i || e < i)
            return;
        if (b == e && b == i)
        {
            t[node][0] = pw[b] * x;
            t[node][1] = pw[n - b + 1] * x;
            return;
        }
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        upd(l, b, mid, i, x);
        upd(r, mid + 1, e, i, x);
        t[node] = merge(t[l], t[r]);
    }
    array<T, 2> query(int node, int b, int e, int i, int j)
    {
        if (b > j || e < i)
            return {T({0, 0}), T({0, 0})};
        if (b >= i && e <= j)
            return t[node];
        int mid = (b + e) >> 1, l = node << 1, r = l | 1;
        return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
    }
    Hashing() {}
    Hashing(string _s)
    {
        n = _s.size();
        s = "." + _s;
        t.resize(4 * n + 1);
        build(1, 1, n);
    }
    void upd(int i, char c)
    {
        upd(1, 1, n, i, c);
        s[i] = c;
    }
    T get_hash(int l, int r)
    { // 1 - indexed
        return query(1, 1, n, l, r)[0] * ipw[l - 1];
    }
    T rev_hash(int l, int r)
    { // 1 - indexed
        return query(1, 1, n, l, r)[1] * ipw[n - r];
    }
    T get_hash()
    {
        return get_hash(1, n);
    }
    bool is_palindrome(int l, int r)
    {
        return get_hash(l, r) == rev_hash(l, r);
    }
};
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    prec();
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        ll n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        Hashing hs(s);
        while (q--)
        {
            ll ty, pos, l, r;
            char c;
            cin >> ty;
            if (ty == 1)
            {
                cin >> pos >> c;
                hs.upd(pos, c);
            }
            else
            {
                cin >> l >> r;
                if (hs.is_palindrome(l, r))
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
        }

        cout << "\n";
    }

    return 0;
} // https://cses.fi/problemset/task/2420