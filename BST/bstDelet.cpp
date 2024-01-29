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
};

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

Node *delet(Node *root, int target)
{
    // base case
    if (!root)
        return root;
    if (root->val < target)
    {
        root->right = delet(root->right, target);
        return root;
    }
    else if (root->val > target)
    {
        root->left = delet(root->left, target);
        return root;
    }
    else
    {
        if (!root->left)
        {
            Node *tmp = root->right;
            delete root;
            return tmp;
        }
        else if (!root->right)
        {
            Node *tmp = root->left;
            delete root;
            return tmp;
        }
        else
        {

            Node *succparent = root;
            Node *succ = root->right;

            while (succ->left != NULL)
            {
                succparent = succ;
                succ = succ->left;
            }

            if (succparent != root)
                succparent->left = succ->right;
            else
                succparent->right = succ->right;
            root->val = succ->val;

            delete succ;
            return root;
        }
    }
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

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Node st, *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 70);

    inOrder(root);

    root = delet(root, 20);
    cout << "\n";

    inOrder(root);
    root = delet(root, 70);
    cout << "\n";

    inOrder(root);
    root = insert(root, 80);
    cout << "\n";
    inOrder(root);
    root = insert(root, 70);
    root = insert(root, 90);
    cout << "\n";
    inOrder(root);
    root = delet(root, 50);
    cout << "\n";
    inOrder(root);
    return 0;
}
