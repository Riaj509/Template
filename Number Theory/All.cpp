inline void normal(ll &a)
{
    a %= MOD;
    (a < 0) && (a += MOD);
}
inline ll modMul(ll a, ll b)
{
    a %= MOD, b %= MOD;
    normal(a), normal(b);
    return (a * b) % MOD;
}
inline ll modAdd(ll a, ll b)
{
    a %= MOD, b %= MOD;
    normal(a), normal(b);
    return (a + b) % MOD;
}
inline ll modSub(ll a, ll b)
{
    a %= MOD, b %= MOD;
    normal(a), normal(b);
    a -= b;
    normal(a);
    return a;
}
inline ll modPow(ll b, ll p)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
            r = modMul(r, b);
        b = modMul(b, b);
        p >>= 1;
    }
    return r;
}
inline ll modInverse(ll a) { return modPow(a, MOD - 2); }
inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }
//////nCr////////
ll powmod(ll x, ll y, ll md)
{
    x %= md;
    if (x == 0)
    {
        return 0;
    }
    ll res = 1;
    while (y > 0)
    {
        if (y % 2 == 1)
        {
            res *= x;
            res %= md;
        }
        x *= x;
        x %= md;
        y /= 2;
    }
    return res;
}
ll inv(ll n, ll md)
{
    return powmod(n, md - 2, md);
}
ll nCk(ll n, ll k, ll md)
{
    return (fact[n] * inv(fact[k], md) % md) * inv(fact[n - k], md) % md;
}

//////// 4 direction//////

ll dx[4] = {0, 1, -1, 0};
ll dy[4] = {1, 0, 0, -1};

///////8 direction/////////

int dx1[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy1[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

////custom_hash////////
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

/*
accesss :
unordered_map<long long, int, custom_hash> safe_map;
gp_hash_table<long long, int, custom_hash> safe_hash_table;
*/

//////////////seive//////////////////////

const int MX = 2e7 + 123;
bitset<MX> is_prime;
vector<int> prime;

void seive(int n)
{
    n += 100;
    for (int i = 3; i <= n; i += 2)
        is_prime[i] = 1;

    int sq = sqrt(n);
    for (int i = 3; i <= sq; i += 2)
    {
        if (is_prime[i] == 1)
        {
            for (int p = i * i; p <= n; p += (i + i))
            {
                is_prime[p] = 0;
            }
        }
    }

    is_prime[2] = 1;
    prime.push_back(2);

    for (int i = 3; i <= n; i += 2)
    {
        if (is_prime[i] == 1)
            prime.push_back(i);
    }
}

////////prime generate upto 1e9//////

// credit: min_25
// takes 0.5s for n = 1e9
vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15)
{
    static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
    struct P
    {
        P(int p) : p(p) {}
        int p;
        int pos[8];
    };
    auto approx_prime_count = [](const int N) -> int
    {
        return N > 60184 ? N / (log(N) - 1.1)
                         : max(1., N / (log(N) - 1.11)) + 1;
    };

    const int v = sqrt(N), vv = sqrt(v);
    vector<bool> isp(v + 1, true);
    for (int i = 2; i <= vv; ++i)
        if (isp[i])
        {
            for (int j = i * i; j <= v; j += i)
                isp[j] = false;
        }

    const int rsize = approx_prime_count(N + 30);
    vector<int> primes = {2, 3, 5};
    int psize = 3;
    primes.resize(rsize);

    vector<P> sprimes;
    size_t pbeg = 0;
    int prod = 1;
    for (int p = 7; p <= v; ++p)
    {
        if (!isp[p])
            continue;
        if (p <= Q)
            prod *= p, ++pbeg, primes[psize++] = p;
        auto pp = P(p);
        for (int t = 0; t < 8; ++t)
        {
            int j = (p <= Q) ? p : p * p;
            while (j % 30 != rs[t])
                j += p << 1;
            pp.pos[t] = j / 30;
        }
        sprimes.push_back(pp);
    }

    vector<unsigned char> pre(prod, 0xFF);
    for (size_t pi = 0; pi < pbeg; ++pi)
    {
        auto pp = sprimes[pi];
        const int p = pp.p;
        for (int t = 0; t < 8; ++t)
        {
            const unsigned char m = ~(1 << t);
            for (int i = pp.pos[t]; i < prod; i += p)
                pre[i] &= m;
        }
    }

    const int block_size = (L + prod - 1) / prod * prod;
    vector<unsigned char> block(block_size);
    unsigned char *pblock = block.data();
    const int M = (N + 29) / 30;

    for (int beg = 0; beg < M; beg += block_size, pblock -= block_size)
    {
        int end = min(M, beg + block_size);
        for (int i = beg; i < end; i += prod)
        {
            copy(pre.begin(), pre.end(), pblock + i);
        }
        if (beg == 0)
            pblock[0] &= 0xFE;
        for (size_t pi = pbeg; pi < sprimes.size(); ++pi)
        {
            auto &pp = sprimes[pi];
            const int p = pp.p;
            for (int t = 0; t < 8; ++t)
            {
                int i = pp.pos[t];
                const unsigned char m = ~(1 << t);
                for (; i < end; i += p)
                    pblock[i] &= m;
                pp.pos[t] = i;
            }
        }
        for (int i = beg; i < end; ++i)
        {
            for (int m = pblock[i]; m > 0; m &= m - 1)
            {
                primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
            }
        }
    }
    assert(psize <= rsize);
    while (psize > 0 && primes[psize - 1] > N)
        --psize;
    primes.resize(psize);
    return primes;
}
///// factorize/////
vector<long long> factorize(long long n)
{
    vector<long long> ret;
    for (auto p : prime)
    {
        if (1LL * p * p > n)
            break;

        if (n % p == 0)
        {
            while (n % p == 0)
            {
                n /= p;
                ret.push_back(p);
            }
        }
    }

    if (n > 1)
        ret.push_back(n);

    return ret;
}

/////////inclution-exclution/////////
ll inc_exc(ll r, vector<ll> &p)
{
    ll sum = 0;
    for (ll msk = 1; msk < (1 << p.size()); ++msk)
    {
        ll mult = 1,
           bits = 0;
        for (ll i = 0; i < p.size(); ++i)
            if (msk & (1 << i))
            {
                ++bits;
                mult *= p[i];
            }

        ll cur = r / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }

    return r - sum;
}

//////SPF-> smallest prime factor////////
const int N = 10000000;
int spf[N + 1];
void sieve()
{
    spf[1] = 1;
    for (ll i = 2; i <= N; ++i)
        spf[i] = i;
    for (int i = 4; i <= N; i = i + 2)
        spf[i] = 2;
    for (int i = 3; i * i <= N; i += 2)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= N; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

void factor(int val, vector<int> &prime)
{
    while (val != 1)
    {
        int p = spf[val];
        prime.push_back(p);
        while (val % p == 0)
            val = val / p;
    }
}
/// euler totient///
vector<ll> phi;
void phi_fn(ll n)
{
    phi.resize(n + 1);
    for (ll i = 0; i <= n; i++)
        phi[i] = i;
    for (ll i = 2; i <= n; i++)
    {
        if (phi[i] == i)
        {
            for (ll j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// most significant bit//
ll MSB(ll x)
{
    for (int i = 31; i >= 0; i--)
    {
        if ((x >> i) & 1)
        {
            return i;
        }
    }
    return -1;
}
// Xor value 1  to n//
ll computeXOR(ll n)
{
    if (n % 4 == 0)
        return n;
    if (n % 4 == 1)
        return 1;
    if (n % 4 == 2)
        return n + 1;
    else
        return 0;
}