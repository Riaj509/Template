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
    Node *left, *right;
    int val;
    Node()
    {
        this->left = this->right = NULL;
    }
    Node(int val)
    {
        this->left = this->right = NULL;
        this->val = val;
    }

    Node *insert(Node *root, int val)
    {
        if (!root)
        {
            return new Node(val);
        }
        if (val > root->val)
            root->right = insert(root->right, val);
        else
            root->left = insert(root->left, val);
        return root;
    }

    void inOrder(Node *root)
    {
        if (!root)
        {
            return;
        }
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    Node st, *root = NULL;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if (i == 0)
            root = st.insert(root, a);
        else
            st.insert(root, a);
    }
    st.inOrder(root);

    return 0;
}
