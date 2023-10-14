#include <bits/stdc++.h>

using namespace std;

// find maximum value (x^a[j]) in the range (l,r) where l<=j<=r
const int N = 1e5 + 100;
const int K = 15;

struct node_t;
typedef node_t *pnode;

struct node_t
{
    int time;
    pnode to[2];
    node_t() : time(0)
    {
        to[0] = to[1] = 0;
    }
    bool go(int l) const
    {
        if (!this)
            return false;
        return time >= l;
    }
    pnode clone()
    {
        pnode cur = new node_t();
        if (this)
        {
            cur->time = time;
            cur->to[0] = to[0];
            cur->to[1] = to[1];
        }
        return cur;
    }
};

pnode last;
pnode version[N];

void insert(int a, int time)
{
    pnode v = version[time] = last = last->clone();
    for (int i = K - 1; i >= 0; --i)
    {
        int bit = (a >> i) & 1;
        pnode &child = v->to[bit];
        child = child->clone();
        v = child;
        v->time = time;
    }
}

int query(pnode v, int x, int l)
{
    int ans = 0;
    for (int i = K - 1; i >= 0; --i)
    {
        int bit = (x >> i) & 1LL;
        if (v->to[bit]->go(l))
        { // checking if this bit was inserted before the range
            ans |= 1 << i;
            v = v->to[bit];
        }
        else
        {
            v = v->to[bit ^ 1];
        }
    }
    return ans;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    last = 0;
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%d", &a);
        insert(a, i);
    }
    while (q--)
    {
        int x, l, r;
        cin >> x >> l >> r;
        --l, --r;
        cout << query(version[r], ~x, l) << "\n";
        // Trie version[r] contains the trie for [0...r] elements
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    while (tc--)
        solve();
}
