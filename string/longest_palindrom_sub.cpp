#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

int main()
{

    string s, s1;
    cin >> s;
    s1 = s;
    reverse(s1.begin(), s1.end());
    ll n = s.size();

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                continue;
            else if (s[i - 1] == s1[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    cout << dp[n][n] << "\n";

    string ans;
    ll i = n, j = n;
    while (i > 0 && j > 0)
    {
        if (s[i - 1] == s1[j - 1])
        {
            ans += s[i - 1];
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    cout << ans;
}
