//....................................<In the name of Allah>...............................//

//.................................<Bismillahir Rahmanir Rahim>...................................//
// Author : Riaj Uddin
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define Max 1000

class Stack
{
    int tp;

public:
    int v[Max];
    Stack() { tp = -1; }

    bool push(int x)
    {
        if (tp >= Max)
        {
            cout << "Stack overflow\n";
            return false;
        }
        v[++tp] = x;
        return true;
    }

    int pop()
    {
        if (tp < 0)
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        return v[tp--];
    }
    int top()
    {
        if (tp < 0)
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        return v[tp];
    }
    bool isEmpty()
    {
        return tp < 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Stack st;
    st.push(10);
    st.push(20);
    st.push(30);
    cout << st.top() << "\n";
    st.pop();
    st.push(1);
    st.push(100);
    st.pop();
    cout << st.top() << "\n";
    st.pop();
    st.pop();
    st.pop();
    cout << st.pop();
    return 0;
}
