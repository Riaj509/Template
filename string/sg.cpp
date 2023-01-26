
#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

struct segtree
{
    ll k;
    struct Node
    {
        ll sum, psum, sufsum, mxsum, mxsubsm;
        Node()
        {
            sum = psum = sufsum = mxsubsm = mxsum = 0;
        }
    };

    vector<Node> tr;

    segtree(ll n)
    {
        k = 1;
        while (k < n)
            k *= 2;
        k *= 2;
        tr.resize(k);
    }
    void update(ll in, ll x)
    {
        in += k / 2;
        tr[in].psum = tr[in].sum = tr[in].mxsum = tr[in].sufsum = tr[in].mxsubsm = x;
        in /= 2;
        while (in > 0)
        {
            tr[in].sum = tr[2 * in].sum + tr[2 * in + 1].sum;
            tr[in].psum = max(tr[2 * in].psum, tr[2 * in].sum + tr[2 * in + 1].psum);
            tr[in].sufsum = max(tr[2 * in + 1].sufsum, tr[2 * in + 1].sum + tr[2 * in].sufsum);
            tr[in].mxsum = max(tr[in].psum, max(tr[in].sufsum, max(tr[2 * in].mxsum, max(tr[2 * in + 1].mxsum, tr[2 * in].sufsum + tr[2 * in + 1].psum))));
            tr[in].mxsubsm = max(tr[2 * in].mxsubsm, max(tr[2 * in + 1].mxsubsm, tr[2 * in].sufsum + tr[2 * in + 1].psum));
            in /= 2;
        }
    }
    Node max_all(ll l, ll r, ll nod, ll a, ll b)
    {
        if (a > r || b < l)
        {
            Node tmp;
            tmp.psum = tmp.sum = tmp.mxsum = tmp.sufsum = tmp.mxsubsm = 0;
            return tmp;
        }
        if (a >= l && b <= r)
            return tr[nod];

        ll mid = (a + b) >> 1;
        Node x = max_all(l, r, 2 * nod, a, mid);
        Node y = max_all(l, r, 2 * nod + 1, mid + 1, b);
        Node res;
        res.sum = x.sum + y.sum;
        res.psum = max(x.psum, x.sum + y.psum);
        res.sufsum = max(y.sufsum, y.sum + x.sufsum);
        res.mxsum = max(res.psum, max(res.sufsum, max(x.mxsum, max(y.mxsum, x.sufsum + y.psum))));
        res.mxsubsm = max(x.mxsubsm, max(y.mxsubsm, x.sufsum + y.psum));
        return res;
    }

    ll range_max_subsum(ll l, ll r)
    {
        return max_all(l, r, 1, 0, k / 2 - 1).mxsubsm;
    }
    ll range_sum(ll l, ll r)
    {
        return max_all(l, r, 1, 0, k / 2 - 1).sum;
    }
};

int main()
{

    ll n, q;
    cin >> n >> q;
    segtree seg(n);
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        seg.update(i, a);
    }

    while (q--)
    {
    }
}