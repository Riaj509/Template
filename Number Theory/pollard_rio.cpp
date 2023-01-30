#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll MOD = (1LL << 31) - 1;
const ll LIM = 1e9;
typedef long long ll;
ll bigmodMul(ll a, ll b, ll m = MOD) /// O(log n)
{
    ll res = 0;
    for (a %= m, b %= m; b > 0; a <<= 1, b >>= 1)
    {
        if (a >= m)
            a -= m;
        if (b & 1)
        {
            res += a;
            if (res >= m)
                res -= m;
        }
    }

    return res;
}
ll bigmodPow(ll x, ll n, ll m = MOD) /// O(log^2(n))
{
    ll res = 1;
    for (x %= m; n > 0; x = bigmodMul(x, x, m), n >>= 1)
        if (n & 1)
            res = bigmodMul(res, x, m);

    return res;
}

ll pw(ll x, ll n) /// O(log n)
{
    ll res = 1;
    for (; n > 0; x = x * x, n >>= 1)
        if (n & 1)
            res = res * x;

    return res;
}

bool isPrime(ll p) /// O(log^5(p)) - O(log p) rounds performed - O(log^2(p)) primality tests - O(log^2(p)) calculation
{
    if (p < 2)
        return false;
    if (p < 4)
        return true;
    if (p % 2 == 0 || p % 3 == 0)
        return false;

    ll q = p - 1;
    ll k = 0;
    while ((q & 1) == 0) /// O(log p)
        q >>= 1, k++;

    ll a = rand() % (p - 4) + 2;
    ll t = bigmodPow(a, q, p); /// O(log^2(q))

    bool ok = (t == 1) || (t == p - 1);
    for (ll i = 1; i <= k && !ok; i++)
    {                           /// O(log k * log t)
        t = bigmodMul(t, t, p); /// O(log t)
        ok = (t == p - 1);
    }

    return ok;
}

map<ll, ll> M;
ll sqrtn;
ll sum = 0;

vector<ll> prime; /// List of prime numbers
vector<ll> lpf;   /// lpf[x] = Lowest_Prime_Factor of x

void sieve(ll lim = LIM) /// O(n)
{
    prime.assign(1, 2);
    lpf.assign(lim + 1, 2); /// O(n)

    for (ll i = 3; i <= lim; i += 2) /// O(n)
    {
        if (lpf[i] == 2)
            prime.push_back(lpf[i] = i);
        for (ll j = 0; j < lpf.size() && prime[j] <= lpf[i] && prime[j] * i <= lim; ++j)
            lpf[prime[j] * i] = prime[j];
    }
}

ll rho(ll n, ll c)
{ /// O(√(√(n)) * polylog n)
    ll x = 2, y = 2, i = 2, k = 2, d;
    while (true)
    {
        x = (bigmodMul(x, x, n) + c); /// O(log n)
        if (x >= n)
            x -= n;
        d = __gcd(abs(x - y), n); /// O(log n)
        if (d > 1)
            return d;
        if (i++ == k)
            y = x, k <<= 1;
    }
    return n;
}

void big_fact(ll n)
{               /// O(√(√(n)) * polylog n)
    if (n == 1) /// O(1)
        return;

    if (n < 1e+9)
    {                      /// O(√(n) / ln(√(n)) * log n / log log n)
        for (ll p : prime) /// O(pair<ll, ll>(√(n)) * log(M.size)) = O(√(n) / ln(√(n)) * log n / log(log n))
        {
            if (p > sqrtn)
                break;
            while (n % p == 0)
                M[p]++, n /= p; /// O(log_p(n) * log(M.size)) = O(log_p(n) * log(n) / log(log n))
        }

        if (n > 1)
            M[n]++; /// O(log(M.size)) = O(log n / log(log n))
        return;
    }

    if (isPrime(n))            /// O(log^5(n))
        return M[n]++, void(); /// O(log(M.size)) = O(log n / log(log n))

    ll d = n;
    for (ll i = 2; d == n; i++) /// O(√(√(n)) * polylog n)
        d = rho(n, i);          /// O(√(√(n)) * polylog n)

    big_fact(d);
    big_fact(n / d);
}

int main() /// O(√n + √(√(n)) * polylog n)
{

    ll n;
    cin >> n;

    sqrtn = sqrt(n); /// O(√(n))
    sieve(sqrtn);    /// O(√(n))

    srand(time(NULL));
    big_fact(n); /// O(√(√(n)) * polylog n)

    ll sum = 1;
    /// n = ∏(e ∈ M){ e.first ^ e.second }
    /// sum = ∏(divisor prime e.first){ e.first ^ (e.second + 1) - 1) / (e.first - 1) }
    for (pair<ll, ll> e : M)                                    /// O(log n / log(log n))
        sum *= (pw(e.first, e.second + 1) - 1) / (e.first - 1); /// O(log n)

    cout << sum;
    return 0;
}