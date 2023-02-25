//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<ll, ll> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef vector<pair<ll, ll>> vli;
typedef double dl;
typedef map<ll, ll> mp;

#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()
#define mem(a, b) memset(a, b, sizeof(a));
#define sz1 cout << endl;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define infll 0n7f7f7f7f7f7f7f7f
#define fraction(a)               \
    cout.unsetf(ios::floatfield); \
    cout.precision(a);            \
    cout.setf(ios::fixed, ios::floatfield);
//////////////////////////////Debug part////////////////////////////////////

template <typename F, typename S>
ostream &operator<<(ostream &os, const pair<F, S> &p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename F, typename S>
ostream &operator<<(ostream &os, const map<F, S> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << it->first << " = " << it->second;
    }
    return os << "]";
}

#define dbg(args...)            \
    do                          \
    {                           \
        cerr << #args << " : "; \
        faltu(args);            \
    } while (0)

void faltu()
{
    cerr << endl;
}

template <typename T>
void faltu(T a[], ll n)
{
    for (ll i = 0; i < n; ++i)
        cerr << a[i] << ' ';
    cerr << endl;
}

template <typename T, typename... hello>
void faltu(T arg, const hello &...rest)
{
    cerr << arg << ' ';
    faltu(rest...);
}
///////////////////////
const int N = 5e5 + 9;
ll v[N];
struct Node
{
    Node *lft, *ri;
    ll val;
    Node(ll a = 0, Node *x = NULL, Node *y = NULL) : val(a), lft(x), ri(y) {}

    void build(ll a, ll b)
    {
        if (a == b)
        {
            val = v[a];
            return;
        }
        // We reached leaf node, No need more links
        lft = new Node(); // Create new node for Left child
        ri = new Node();  // We are creating nodes only when necessary!

        ll mid = (a + b) >> 1;
        lft->build(a, mid);
        ri->build(mid + 1, b);
        val = lft->val + ri->val;
    }
    Node *update(int a, int b, int idx, int v)
    {
        if (b < idx || a > idx)
            return this; // Out of range, use this node.
        if (a == b)
        { // Leaf Node, create new node and return that.
            Node *ret = new Node(val, lft, ri);
            ret->val += v;
            return ret;
            // we first cloned our current node, then added v to the value.
        }
        int mid = a + b >> 1;
        Node *ret = new Node(val); // Create a new node, as idx in in [l, r]
        ret->lft = lft->update(a, mid, idx, v);
        ret->ri = ri->update(mid + 1, b, idx, v);
        // Note that 'ret -> left' is new node's left child,
        // But 'left' is current old node's left child.
        // So we call to update idx in left child of old node.
        // And use it's return node as new node's left child. Same for right.
        ret->val = ret->lft->val + ret->ri->val; // Update value.
        return ret;                              // Return the new node to parent.
    }
    int query(int a, int b, int i, int j)
    {
        if (b < i || a > j)
            return 0; // out of range
        if (i <= a && b <= j)
        {               // completely inside
            return val; // return value stored in this node
        }
        int mid = a + b >> 1;
        return lft->query(a, mid, i, j) +
               ri->query(mid + 1, b, i, j);
    }
} *root[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        ll n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> v[i];
        root[0] = new Node();
        root[0]->build(1, n);

        ll q, ver = 0;
        cin >> q;
        while (q--)
        {
            ll ty;
            cin >> ty;
            if (ty == 1)
            {
                ll idx, pos, k;
                cin >> idx >> pos >> k;
                root[++ver] = root[idx]->update(1, n, pos, k); ////create new version root[++ver] and link with old version
            }
            else
            {
                ll idx, l, r;
                cin >> idx >> l >> r;
                cout << root[idx]->query(1, n, l, r);
                cout << "\n";
            }
        }

        // cout << "\n";
    }

    return 0;
} // https://www.spoj.com/problems/PSEGTREE/