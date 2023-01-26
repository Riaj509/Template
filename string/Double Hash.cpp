#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
//////0-base index//////

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

///////1-base index///////
// Warning: Change mod and N according to question
const int mod = (1LL << 31) - 1;
const int N = 1e6 + 3;

int rand(int l, int r)
{
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> ludo(l, r);
    return ludo(rng);
}

inline int add(int x, int y, int mod = ::mod)
{
    x += y;
    if (x >= mod or x < 0)
        x %= mod;
    if (x >= 0)
        return x;
    return x + mod;
}
inline int mul(int x, int y, int mod = ::mod)
{
    if (x >= mod or x + mod < 0)
        x %= mod;
    if (y >= mod or y + mod < 0)
        y %= mod;
    x *= y;
    if (x >= mod or x + mod < 0)
        x %= mod;
    if (x >= 0)
        return x;
    return x + mod;
}
inline int sub(int x, int y, int mod = ::mod)
{
    x -= y;
    if (x + mod < 0 or x >= mod)
    {
        x %= mod;
    }
    if (x >= 0)
        return x;
    return x + mod;
}

struct Hash
{
    vector<pair<int, int>> H, pre;
    Hash(string &s, int N, int b1 = 41, int b2 = 53) : H(N + 5), pre(N + 5)
    {
        pre[0].first = 1, b1 = rand(37, 1 << 10);
        pre[0].second = 1, b2 = rand(41, 1 << 9);
        int cur1 = 0, cur2 = 0;
        for (int i = 1; i <= N; ++i)
        {
            pre[i].first = mul(pre[i - 1].first, b1);
            pre[i].second = mul(pre[i - 1].second, b2);
            cur1 = add(mul(cur1, b1), (s[i] - 'a' + 1));
            cur2 = add(mul(cur2, b2), (s[i] - 'a' + 1));
            H[i].first = cur1, H[i].second = cur2;
        }
    }
    pair<int, int> get_hash(int l, int r)
    {
        int rem1 = mul(pre[r - l + 1].first, H[l - 1].first);
        int rem2 = mul(pre[r - l + 1].second, H[l - 1].second);
        return make_pair(sub(H[r].first, rem1), sub(H[r].second, rem2));
    }
};

int main()
{

    return 0;
}