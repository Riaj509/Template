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
const ll mx = 2e5 + 10;
const ll MOD = (1LL << 31) - 1;
ll pw[mx];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    pw[0] = 1;
    ll p = 31;
    for (int i = 1; i < mx; i++)
    {
        pw[i] = (pw[i - 1] * p) % MOD;
    }
    ll tc = 1;
    cin >> tc;
    while (tc--)
    {
        ll n, m, time, q;
        string s[2];
        cin >> s[0] >> s[1] >> time >> q;

        n = s[1].size();
        ll cur_s = 0;
        ll cur_t = 0;
        for (int i = 0; i < n; i++)
            cur_s += (((s[0][i] - 'a') + 1) * pw[i]) % MOD;
        for (int i = 0; i < n; i++)
            cur_t += (((s[1][i] - 'a') + 1) * pw[i]) % MOD;
        // dbg(cur_s, cur_t);
        vl timestamp(q + 1, -1);
        for (int tim = 1; tim <= q; tim++)
        {
            ll opt, idx;
            cin >> opt;
            if (tim > time)
            {
                if (timestamp[tim - time] != -1)
                {
                    ll idx = timestamp[tim - time];
                    cur_s = (cur_s + ((s[0][idx] - 'a' + 1) * pw[idx])) % MOD;
                    cur_t = (cur_t + ((s[1][idx] - 'a' + 1) * pw[idx])) % MOD;
                    timestamp[tim - time] = -1;
                }
            }
            if (opt == 1)
            {
                ll idx;
                cin >> idx;
                idx--;
                cur_s = cur_s - ((s[0][idx] - 'a' + 1) * pw[idx]) % MOD;
                cur_s = (cur_s + MOD) % MOD;
                cur_t = cur_t - ((s[1][idx] - 'a' + 1) * pw[idx]) % MOD;
                cur_t = (cur_t + MOD) % MOD;
                timestamp[tim] = idx;
                // cout << cur_s << " " << cur_t << " 1\n";
            }
            else if (opt == 2)
            {
                ll a, b, idx1, idx2;
                cin >> a >> idx1 >> b >> idx2;
                idx1--, idx2--;
                if (a == 1)
                {
                    cur_s = cur_s - ((s[0][idx1] - 'a' + 1) * pw[idx1]) % MOD;
                    cur_s = (cur_s + MOD) % MOD;
                }
                else if (a == 2)
                {
                    cur_t = cur_t - ((s[1][idx1] - 'a' + 1) * pw[idx1]) % MOD;
                    cur_t = (cur_t + MOD) % MOD;
                }
                if (b == 1)
                {
                    cur_s = cur_s - ((s[0][idx2] - 'a' + 1) * pw[idx2]) % MOD;
                    cur_s = (cur_s + MOD) % MOD;
                }
                else if (b == 2)
                {
                    cur_t = cur_t - ((s[1][idx2] - 'a' + 1) * pw[idx2]) % MOD;
                    cur_t = (cur_t + MOD) % MOD;
                }
                swap(s[a - 1][idx1], s[b - 1][idx2]);
                if (a == 1)
                    cur_s = (cur_s + ((s[0][idx1] - 'a' + 1) * pw[idx1])) % MOD;
                else if (a == 2)
                    cur_t = (cur_t + ((s[1][idx1] - 'a' + 1) * pw[idx1])) % MOD;
                if (b == 1)
                    cur_s = (cur_s + ((s[0][idx2] - 'a' + 1) * pw[idx2])) % MOD;
                else if (b == 2)
                    cur_t = (cur_t + ((s[1][idx2] - 'a' + 1) * pw[idx2])) % MOD;

                // cout << cur_s << " " << cur_t << " 2\n";
            }
            else
            {
                cout << (cur_s == cur_t ? "YES\n" : "NO\n");
            }
        }

        // cout << "\n";
    }
    return 0;
}
// https://codeforces.com/contest/1840/problem/E
