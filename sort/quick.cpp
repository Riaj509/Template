//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &a, int l, int h)
{
    int pivot = a[l];
    int k = h;

    for (int i = h; i > l; i--)
    {
        if (a[i] > pivot)
            swap(a[i], a[k--]);
    }
    swap(a[k], a[l]);
    return k;
}

void quickSort(vector<int> &a, int l, int h)
{
    if (l >= h)
        return;

    int part = partition(a, l, h);
    quickSort(a, l, part - 1);
    quickSort(a, part + 1, h);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &a : v)
        cin >> a;
    quickSort(v, 0, n - 1);
    for (auto u : v)
        cout << u << " ";

    return 0;
}
