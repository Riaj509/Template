#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
int main()
{
    ll N, Q;
    cin >> N >> Q;
    ll forest[N + 1][N + 1], tree_pref[N + 1][N + 1];

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            cin >> forest[i][j];
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            tree_pref[i][j] = forest[i][j] + tree_pref[i - 1][j] + tree_pref[i][j - 1] - tree_pref[i - 1][j - 1];
        }
    }

    for (int q = 0; q < Q; q++)
    {
        int from_row, to_row, from_col, to_col;
        cin >> from_row >> from_col >> to_row >> to_col;
        cout << tree_pref[to_row][to_col] - tree_pref[from_row - 1][to_col] - tree_pref[to_row][from_col - 1] + tree_pref[from_row - 1][from_col - 1] << '\n';
    }
}
