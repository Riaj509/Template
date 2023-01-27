#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        ll Q;
        string s, s1;
        cin >> s >> Q;
        int N = s.size();
        s = '#' + s;

        vector<vector<int>> palin(N + 1, vector<int>(N + 1, 0));
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= N; i++)
        {
            int l = i, r = i;

            while (l >= 1 && r <= N && s[l] == s[r])
                palin[l][r] = 1, l--, r++;
            l = i, r = i + 1;
            while (l >= 1 && r <= N && s[l] == s[r])
                palin[l][r] = 1, l--, r++;
        }
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                dp[i][j] = palin[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            }
        }

        ll l1, r1, l2, r2, l, r;
        while (Q--)
        {
            cin >> l >> r;
            l1 = l, r1 = 1;
            l2 = r2 = r;
            cout << dp[l2][r2] - dp[l1 - 1][r2] - dp[l2][r1 - 1] + dp[l1 - 1][r1 - 1] << '\n';
        }

        cout << "\n";
    }

    return 0;
} // https://codeforces.com/contest/245/problem/H