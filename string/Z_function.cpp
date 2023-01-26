#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll mx = 1e6;
ll z[mx];
void Z_fun(string &s)
{
    ll n = s.size();
    z[0] = 0;
    for (ll i = 1, l = 0, r = 0; i < n; ++i)
    {
        z[i] = 0;
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

bool pattern_match(string &s, ll ln)
{
    ll n = s.size();
    Z_fun(s);

    for (int i = 0; i < n; i++)
    {
        if (z[i + ln] == ln)
            return true;
    }
    return false;
}

bool string_compress(string &s)
{
    ll n = s.size();
    Z_fun(s);
    bool f = false;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            if (z[i] + i == n)
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        string s, p;
        cin >> s >> p;
        ll n = p.size();
        if (string_compress(s))
            cout << "YES";
        else
            cout << "NO";
        cout << "\n";
        p += s;

        if (pattern_match(p, n))
            cout << "YES";
        else
            cout << "NO";
        cout << "\n";
    }

    return 0;
}