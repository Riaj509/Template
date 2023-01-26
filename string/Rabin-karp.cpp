
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll p = 31;
const ll m = 1e9 + 9;

ll rabin_karp(string const &s, string const &t)
{

    ll S = s.size(), T = t.size();

    vector<ll> p_pow(max(S, T));
    p_pow[0] = 1;
    for (ll i = 1; i < (ll)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % m;

    vector<ll> h(T + 1, 0);
    for (ll i = 0; i < T; i++)
        h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
    ll h_s = 0;
    for (ll i = 0; i < S; i++)
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;

    ll cnt = 0;
    for (ll i = 0; i + S - 1 < T; i++)
    {
        ll cur_h = (h[i + S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            cnt++;
    }
    return cnt;
}

int main()
{
    string p, t;
    cin >> t >> p;

    cout << rabin_karp(p, t);
}