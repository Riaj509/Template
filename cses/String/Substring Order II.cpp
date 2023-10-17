#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

const int maxN = 1e5 + 5;

struct Node
{
    ll dp;
    int len, link, cnt, firstpos;
    map<char, int> nxt;
} node[2 * maxN];

string S, T;
int N, M, sz, last, bestln = -1, bestidx;
ll K;
bool vis[3 * maxN];
vector<char> ans;

void extend(char c)
{
    int cur = sz++;
    node[cur].len = node[last].len + 1;
    node[cur].cnt = 1;
    node[cur].firstpos = node[cur].len - 1;
    int p = last;
    while (p != -1 && !node[p].nxt.count(c))
    {
        node[p].nxt[c] = cur;
        p = node[p].link;
    }
    if (p == -1)
    {
        node[cur].link = 0;
    }
    else
    {
        int q = node[p].nxt[c];
        if (node[p].len + 1 == node[q].len)
        {
            node[cur].link = q;
        }
        else
        {
            int clone = sz++;
            node[clone].len = node[p].len + 1;
            node[clone].nxt = node[q].nxt;
            node[clone].link = node[q].link;
            node[clone].firstpos = node[q].firstpos;
            while (p != -1 && node[p].nxt[c] == q)
            {
                node[p].nxt[c] = clone;
                p = node[p].link;
            }
            node[q].link = node[cur].link = clone;
        }
    }
    last = cur;
}

void init()
{
    node[0].len = 0;
    node[0].link = -1;
    sz = 1;
    last = 0;
}

void update_cnt()
{
    vector<int> state_sz[sz];
    for (int i = 0; i < sz; i++)
        state_sz[node[i].len].push_back(i);
    for (int i = sz - 1; i >= 0; i--)
    {
        for (auto u : state_sz[i])
        {
            if (node[u].link != -1)
                node[node[u].link].cnt += node[u].cnt;
        }
    }
}
int query_fidx()
{
    int u = 0;
    for (int i = 0; i < M; i++)
    {
        char c = T[i];
        if (!node[u].nxt.count(c))
            return -1;
        else
            u = node[u].nxt[c];
    }
    return node[u].firstpos - M + 2;
}

void lng_repeat_str(int u = 0)
{
    vis[u] = true;
    for (const auto v : node[u].nxt)
    {
        if (node[u].len > bestln && node[u].cnt > 1 && u != 0)
        {
            bestln = node[u].len;
            bestidx = node[u].firstpos - node[u].len + 1;
        }
        if (!vis[v.second])
            lng_repeat_str(v.second);
    }
}
void distnt_substr(int u = 0)
{
    node[u].dp = node[u].cnt;
    for (const auto v : node[u].nxt)
    {
        if (!node[v.second].dp)
            distnt_substr(v.second);
        node[u].dp += node[v.second].dp;
    }
}
void kth_lex_str(ll u, ll k)
{
    if (k < 0)
        return;
    for (const auto v : node[u].nxt)
    {
        if (node[v.second].dp <= k)
            k -= node[v.second].dp;
        else
        {
            ans.push_back(v.first);
            kth_lex_str(v.second, k - node[v.second].cnt);
            return;
        }
    }
}

int query_cnt()
{
    int u = 0;
    for (int i = 0; i < M; i++)
    {
        char c = T[i];
        if (!node[u].nxt.count(c))
            return 0;
        else
            u = node[u].nxt[c];
    }
    return node[u].cnt;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--)
    {
        cin >> S >> K;
        N = S.size();
        init();

        for (int i = 0; i < N; i++)
            extend(S[i]);
        update_cnt();
        distnt_substr();
        kth_lex_str(0, K - 1);
        for (auto u : ans)
            cout << u;

        cout << "\n";
    }
}