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
    Node(int val) { this->left = NULL, this->right = NULL, this->val = val; }
};

void preOrder(Node *root)
{
    if (!root)
        return;
    cout << root->val << " ";

    preOrder(root->left);

    preOrder(root->right);
}
void inOrder(Node *root)
{
    if (!root)
        return;
    inOrder(root->left);

    cout << root->val << " ";

    inOrder(root->right);
}
void postOrder(Node *root)
{
    if (!root)
        return;
    postOrder(root->left);

    postOrder(root->right);

    cout << root->val << " ";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    preOrder(root);
    cout << "\n";
    inOrder(root);
    cout << "\n";
    postOrder(root);

    return 0;
}
