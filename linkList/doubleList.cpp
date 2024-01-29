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
    Node *next, *prev;
    int val;
    Node()
    {
        this->next = this->prev = NULL;
    }
    Node(int val)
    {
        this->next = this->prev = NULL;
        this->val = val;
    }
};

class DoubleList
{
public:
    Node *head;
    DoubleList() { head = NULL; }

    void print()
    {
        Node *tmp = head;
        while (tmp != NULL)
        {
            cout << " " << tmp->val;
            if (tmp->prev != NULL)
            {
                cout << " Prev: " << tmp->prev->val;
            }
            if (tmp->next != NULL)
            {
                cout << " Next: " << tmp->next->val;
            }
            tmp = tmp->next;
        }
    }

    void delet(int val)
    {
        Node *cur = head, *done = NULL;
        while (cur != NULL)
        {
            if (cur->val == val)
            {
                done = cur;
                break;
            }
            cur = cur->next;
        }
        if (done == NULL)
            return;
        Node *ageh = done->prev;
        Node *pore = done->next;
        delete (done);
        ageh->next = pore;
        pore->prev = ageh;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    DoubleList lst;

    // Add first node
    Node *first = new Node(1);
    lst.head = first;

    // Add  node
    Node *second = new Node(2);
    second->prev = first;
    first->next = second;

    // Add  node
    Node *third = new Node(3);
    third->prev = second;
    second->next = third;

    // print
    lst.print();
    cout << "\n";
    lst.delet(2);
    lst.print();

    return 0;
}
