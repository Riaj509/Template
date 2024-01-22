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
    Node(int val) { this->next = NULL, this->val = val; }
};

class Linklist
{
    Node *list;

public:
    Linklist() { list = NULL; }

    void insert(int x)
    {
        Node *nw = new Node(x); // create new node
        if (list == NULL)
        {
            list = nw;
            return;
        }
        Node *cur = list;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = nw;
    }

    void deletvalue(int x)
    {
        Node *cur = list;
        if (cur == NULL)
        {
            cout << "List Empty\n";
            return;
        }
        if (cur->val == x)
        {
            list = list->next;
            return;
        }
        while (cur != NULL)
        {
            if (cur->next->val == x)
            {
                cur->next = cur->next->next;
                break;
            }
        }
    }
    void deletkthnode(int k)
    {
        Node *cur = list;
        Node *now = list;
        if (cur == NULL)
        {
            cout << "List Empty\n";
            return;
        }

        int ln = 0;
        while (cur != NULL)
            cur = cur->next, ++ln;
        if (ln < k)
        {
            cout << "Out of range\n";
            return;
        }
        if (k == 1)
        {
            list = list->next;
            return;
        }
        while (--k > 1)
            now = now->next;
        now->next = now->next->next;
    }

    void show()
    {
        Node *cur = list;
        while (cur != NULL)
        {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << "\n";
        return;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Linklist lst;

    lst.insert(1);
    lst.insert(2);
    lst.insert(3);
    lst.insert(4);
    lst.insert(5);
    lst.deletvalue(2);
    lst.show();
    lst.deletvalue(1);
    lst.show();
    lst.insert(1);
    lst.insert(5);
    lst.insert(6);
    lst.show();
    lst.deletkthnode(7);
    lst.show();
    lst.deletkthnode(4);
    lst.show();
    lst.deletkthnode(2);
    lst.show();

    return 0;
}
