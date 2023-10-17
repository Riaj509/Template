#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
// Warning: Change mod and N according to question
const int mod = (1LL << 31) - 1;
const int N = 1e6 + 3;

#define int long long
#define MP make_pair
#define F first
#define S second
#define sz(s) ((int)s.size())

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

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        string s;
        cin >> s;
        ll n = s.size();
        s = '#' + s;

        Hash hs(s, n);
        vector<ll> ans;
        for (int ln = 1; ln <= n; ln++)
        {
            auto seg = hs.get_hash(1, ln);
            bool f = true;
            for (int i = ln + ln; i <= n && f; i += ln)
            {
                f &= (hs.get_hash(i - ln + 1, i) == seg);
            }
            ll baki = n / ln * ln;
            if (baki != n)
            {
                ll rem = n - baki;
                f &= (hs.get_hash(1, rem) == hs.get_hash(baki + 1, n));
            }
            if (f)
                ans.push_back(ln);
        }
        for (auto u : ans)
            cout << u << " ";
        cout << "\n";
    }

    return 0;
}
