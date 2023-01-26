const ll MOD = 1e9 + 7;
const ll mx = 2e5 + 1;
ll fact[mx];
ll invfact[mx];
struct combin
{
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

    void fct()
    {
        fact[0] = invfact[0] = 1;
        for (int i = 1; i < mx; i++)
        {
            fact[i] = modMul(fact[i - 1], i);
            invfact[i] = modMul(invfact[i - 1], modInverse(i));
        }
    }
} com;