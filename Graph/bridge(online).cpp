//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
/// Author : Riaj Uddin

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (int)x.size()
#define mem(a) memset(a, 0, sizeof a)
#define lower(a, b) lower_bound((a).begin(), (a).end(), b) - (a).begin()

//////////////////////////////////////////////////

// A bridge is defined as an edge which, when removed, makes the graph disconnected (or more precisely, increases the number of connected components in the graph).

const ll mx = 1e4;
ll n, m;
vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
int bridges;
int lca_iteration;
vector<int> last_visit;
struct bridge
{
    int find_2ecc(int v)
    {
        if (v == -1)
            return -1;
        return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
    }

    int find_cc(int v)
    {
        v = find_2ecc(v);
        return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(dsu_cc[v]);
    }

    void make_root(int v)
    {
        v = find_2ecc(v);
        int root = v;
        int child = -1;
        while (v != -1)
        {
            int p = find_2ecc(par[v]);
            par[v] = child;
            dsu_cc[v] = root;
            child = v;
            v = p;
        }
        dsu_cc_size[root] = dsu_cc_size[child];
    }

    void merge_path(int a, int b)
    {
        ++lca_iteration;
        vector<int> path_a, path_b;
        int lca = -1;
        while (lca == -1)
        {
            if (a != -1)
            {
                a = find_2ecc(a);
                path_a.push_back(a);
                if (last_visit[a] == lca_iteration)
                {
                    lca = a;
                    break;
                }
                last_visit[a] = lca_iteration;
                a = par[a];
            }
            if (b != -1)
            {
                b = find_2ecc(b);
                path_b.push_back(b);
                if (last_visit[b] == lca_iteration)
                {
                    lca = b;
                    break;
                }
                last_visit[b] = lca_iteration;
                b = par[b];
            }
        }

        for (int v : path_a)
        {
            dsu_2ecc[v] = lca;
            if (v == lca)
                break;
            --bridges;
        }
        for (int v : path_b)
        {
            dsu_2ecc[v] = lca;
            if (v == lca)
                break;
            --bridges;
        }
    }

    void add_edge(int a, int b)
    {
        a = find_2ecc(a);
        b = find_2ecc(b);
        if (a == b)
            return;

        int ca = find_cc(a);
        int cb = find_cc(b);

        if (ca != cb)
        {
            ++bridges;
            if (dsu_cc_size[ca] > dsu_cc_size[cb])
            {
                swap(a, b);
                swap(ca, cb);
            }
            make_root(a);
            par[a] = dsu_cc[a] = b;
            dsu_cc_size[cb] += dsu_cc_size[a];
        }
        else
        {
            merge_path(a, b);
        }
    }
    void init(int n)
    {
        par.resize(n);
        dsu_2ecc.resize(n);
        dsu_cc.resize(n);
        dsu_cc_size.resize(n);
        lca_iteration = 0;
        last_visit.assign(n, 0);
        for (int i = 0; i < n; ++i)
        {
            dsu_2ecc[i] = i;
            dsu_cc[i] = i;
            dsu_cc_size[i] = 1;
            par[i] = -1;
        }
        bridges = 0;
    }
} br;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        cin >> n >> m;
        br.init(n);
        while (m--)
        {
            int ty;
            ll a, b;
            if (ty == 1)
            {
                cin >> a >> b;
                br.add_edge(a, b);
            }
            else
                cout << bridges << '\n';
        }

        // cout << "\n";
    }
    return 0;
}