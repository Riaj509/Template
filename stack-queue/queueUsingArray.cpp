//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define Max 1000

class Queue
{
public:
    int tp, btm;

public:
    int v[Max];
    Queue() { tp = -1, btm = -1; }

    bool push(int x)
    {
        if (btm >= Max)
        {
            cout << "Stack overflow\n";
            return false;
        }
        if (tp == -1)
            tp = 0;
        v[++btm] = x;
        return true;
    }

    int pop()
    {
        if (tp == -1 || tp > btm)
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        return v[tp++];
    }
    int top()
    {
        if (tp == -1 || tp > btm)
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        return v[tp];
    }
    bool isEmpty()
    {
        return (tp == btm || tp > btm);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Queue q;
    q.push(10);
    q.push(20);
    q.push(40);
    cout << q.top() << "\n";
    cout << q.pop() << "\n";
    cout << q.pop() << "\n";
    cout << q.top() << "\n";
    q.push(5);
    cout << q.pop() << "\n";
    cout << q.pop() << "\n";
    cout << q.top();

    return 0;
}
