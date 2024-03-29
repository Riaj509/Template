#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define all int(a)(a).begin(), (a).end()
#define rall int(a)(a).rbegin(), (a).rend()
#define F first
#define S second
#define mem(a, b) memset(a, b, sizeof(a))
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()

//////////////////////////////////////////////////
const int N = 1e5;
const int K = 18;
int st[N][K];
int lg[N];
vector<vector<int>> c;
struct suffix_array
{
    vector<int> sort_cyclic_shifts(string const &s)
    {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), cnt(alphabet, 0);
        c.clear();
        c.emplace_back();
        c[0].resize(n);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[0][p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        cnt.resize(n);
        for (int h = 0; (1 << h) < n; h++)
        {
            for (int i = 0; i < n; i++)
            {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.end(), 0);
            /// radix sort
            for (int i = 0; i < n; i++)
                cnt[c[h][pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[h][pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[h][p[i - 1]], c[h][(p[i - 1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.push_back(cn);
        }
        return p;
    }
    vector<int> suffix_array_construction(string s)
    {
        s += "!";
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }
    /// compare two suffixes starting at i and j with length 2^k
    int compare(int i, int j, int n, int k)
    {
        pair<int, int> a = {c[k][i], c[k][(i + 1 - (1 << k)) % n]};
        pair<int, int> b = {c[k][j], c[k][(j + 1 - (1 << k)) % n]};
        return (a == b ? 0 : a < b ? -1
                                   : 1);
    }
    int lcp_(int i, int j)
    {
        int log_n = c.size() - 1;
        int ans = 0;
        for (int k = log_n; k >= 0; k--)
        {
            if (c[k][i] == c[k][j])
            {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
    vector<int> lcp_construction(string const &s, vector<int> const &p)
    {
        int n = s.size();
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++)
            rank[p[i]] = i;
        int k = 0;
        vector<int> lcp(n - 1, 0);
        for (int i = 0; i < n; i++)
        {
            if (rank[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }

    void pre()
    {
        lg[1] = 0;
        for (int i = 2; i < N; i++)
            lg[i] = lg[i / 2] + 1;
    }
    void build(vector<int> &lcp)
    {
        int n = lcp.size();
        for (int i = 0; i < n; i++)
            st[i][0] = lcp[i];
        for (int k = 1; k < K; k++)
            for (int i = 0; i < n; i++)
            {
                st[i][k] = st[i][k - 1];
                int nxt = i + (1 << (k - 1));
                if (nxt >= n)
                    continue;
                st[i][k] = min(st[i][k], st[nxt][k - 1]);
            }
    }
} suf;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        suf.pre();
        string s;
        cin >> s;
        int n = s.size();
        vector<int> sa = suf.suffix_array_construction(s);
        vector<int> lcp = suf.lcp_construction(s, sa);
        suf.build(lcp);
        for (int i = 0; i < n - 1; i++)
            cout << sa[i] << "\n";
        cout << "\n";
    }
    return 0;
}
