//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *next;
    int val;
    Node(int val)
    {
        this->next = NULL;
        this->val = val;
    }
};

Node *solve(vector<int> &v)
{
    Node *list = new Node(0);

    Node *cur = list;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        Node *nw = new Node(v[i]);
        cur->next = nw;
        cur = cur->next;
    }
    return list->next;
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
    Node *list = solve(v);
    while (list != NULL)
    {
        cout << list->val << " ";
        list = list->next;
    }

    return 0;
}

