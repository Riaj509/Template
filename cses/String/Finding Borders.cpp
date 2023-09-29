#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll power(ll x, ll y, ll p)
{
    ll result = 1;
    for (; y; y >>= 1, x = x * x % p)
    {
        if (y & 1)
        {
            result = result * x % p;
        }
    }
    return result;
}

ll inverse(ll x, ll p)
{
    return power(x, p - 2, p);
}

class Hash
{
private:
    ll length;
    const ll mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    const ll p1 = 31, p2 = 37;
    vector<ll> hash1, hash2;
    pair<ll, ll> hash_pair;

public:
    vector<ll> inv_pow1, inv_pow2;
    int inv_size = 1;

    Hash() {}

    Hash(const string &s)
    {
        length = s.size();
        hash1.resize(length);
        hash2.resize(length);

        ll h1 = 0, h2 = 0;
        ll p_pow1 = 1, p_pow2 = 1;
        for (ll i = 0; i < length; i++)
        {
            h1 = (h1 + (s[i] - 'a' + 1) * p_pow1) % mod1;
            h2 = (h2 + (s[i] - 'a' + 1) * p_pow2) % mod2;
            p_pow1 = (p_pow1 * p1) % mod1;
            p_pow2 = (p_pow2 * p2) % mod2;
            hash1[i] = h1;
            hash2[i] = h2;
        }
        hash_pair = make_pair(h1, h2);

        if (inv_size < length)
        {
            for (; inv_size < length; inv_size <<= 1)
                ;

            inv_pow1.resize(inv_size, -1);
            inv_pow2.resize(inv_size, -1);

            inv_pow1[inv_size - 1] = inverse(power(p1, inv_size - 1, mod1), mod1);
            inv_pow2[inv_size - 1] = inverse(power(p2, inv_size - 1, mod2), mod2);

            for (ll i = inv_size - 2; i >= 0 && inv_pow1[i] == -1; i--)
            {
                inv_pow1[i] = (1LL * inv_pow1[i + 1] * p1) % mod1;
                inv_pow2[i] = (1LL * inv_pow2[i + 1] * p2) % mod2;
            }
        }
    }

    ll size()
    {
        return length;
    }

    pair<ll, ll> prefix(const ll index)
    {
        return {hash1[index], hash2[index]};
    }

    pair<ll, ll> substr(const ll l, const ll r)
    {
        if (l == 0)
        {
            return {hash1[r], hash2[r]};
        }
        ll temp1 = hash1[r] - hash1[l - 1];
        ll temp2 = hash2[r] - hash2[l - 1];
        temp1 += (temp1 < 0 ? mod1 : 0);
        temp2 += (temp2 < 0 ? mod2 : 0);
        temp1 = (temp1 * 1LL * inv_pow1[l]) % mod1;
        temp2 = (temp2 * 1LL * inv_pow2[l]) % mod2;
        return {temp1, temp2};
    }

    bool operator==(const Hash &other)
    {
        return (hash_pair == other.hash_pair);
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s, s1;
    cin >> s;
    auto cur = Hash(s);

    for (int i = 0; i < s.size() - 1; i++)
    {
        if (cur.substr(0, i) == cur.substr(s.size() - i - 1, s.size() - 1))
            cout << i + 1 << " ";
    }

    cout << '\n';
    return 0;
} // https://cses.fi/problemset/task/1732/