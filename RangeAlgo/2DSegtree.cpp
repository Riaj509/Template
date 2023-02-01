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

//////////////////////////////-------->
const int mx = 1e3 + 10;
ll a[mx][mx];
ll n, m, q;
struct multi_segtree
{
    ll t[4 * mx][4 * mx];

    void build_y(int vx, int lx, int rx, int vy, int ly, int ry)
    {
        if (ly == ry)
        {
            if (lx == rx)
                t[vx][vy] = a[lx][ly];
            else
                t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
        }
        else
        {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy * 2, ly, my);
            build_y(vx, lx, rx, vy * 2 + 1, my + 1, ry);
            t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
        }
    }

    void build_x(int vx, int lx, int rx)
    {
        if (lx != rx)
        {
            int mx = (lx + rx) / 2;
            build_x(vx * 2, lx, mx);
            build_x(vx * 2 + 1, mx + 1, rx);
        }
        build_y(vx, lx, rx, 1, 0, m - 1);
    }
    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val)
    {
        if (ly == ry)
        {
            if (lx == rx)
                t[vx][vy] = new_val;
            else
                t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
        }
        else
        {
            int my = (ly + ry) / 2;
            if (y <= my)
                update_y(vx, lx, rx, vy * 2, ly, my, x, y, new_val);
            else
                update_y(vx, lx, rx, vy * 2 + 1, my + 1, ry, x, y, new_val);
            t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
        }
    }

    void update_x(int vx, int lx, int rx, int x, int y, int new_val)
    {
        if (lx != rx)
        {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                update_x(vx * 2, lx, mx, x, y, new_val);
            else
                update_x(vx * 2 + 1, mx + 1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 1, 0, m - 1, x, y, new_val);
    }

    int sum_y(int vx, int vy, int tly, int try_, int ly, int ry)
    {
        if (ly > ry)
            return 0;
        if (ly == tly && try_ == ry)
            return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return sum_y(vx, vy * 2, tly, tmy, ly, min(ry, tmy)) + sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(ly, tmy + 1), ry);
    }

    int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry)
    {
        if (lx > rx)
            return 0;
        if (lx == tlx && trx == rx)
            return sum_y(vx, 1, 0, m - 1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return sum_x(vx * 2, tlx, tmx, lx, min(rx, tmx), ly, ry) + sum_x(vx * 2 + 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
    }
} multi;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        cin >> n >> q;
        m = n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;
                cin >> c;
                if (c == '.')
                    a[i][j] = 0;
                else
                    a[i][j] = 1;
            }
        }
        multi.build_x(1, 0, n - 1);

        while (q--)
        {
            int typ, x, y, l1, r1, l2, r2;
            cin >> typ;
            if (typ == 1)
            {
                cin >> x >> y;
                --x, --y;
                a[x][y] = 1 - a[x][y];
                multi.update_x(1, 0, n - 1, x, y, a[x][y]);
            }
            else
            {
                cin >> l1 >> r1 >> l2 >> r2;
                --l1, --l2, --r1, --r2;
                cout << multi.sum_x(1, 0, n - 1, l1, l2, r1, r2) << "\n";
            }
        }
    }

    return 0;
} // https: // cses.fi/problemset/task/1739
