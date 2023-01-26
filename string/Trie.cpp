#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Node
{

    Node *link[10];
    bool ends = false;

    bool containsKey(int ch)
    {
        return (link[ch] != NULL);
    }
    void put(int ch, Node *n)
    {
        link[ch] = n;
    }
    Node *get(int c)
    {
        return link[c];
    }
    void setEnd() { ends = true; }

    bool isEnd() { return ends; }
};

class Trie
{
public:
    Node *head;
    Trie()
    {
        head = new Node();
    }

    void insert(vector<int> word)
    {
        Node *node = head;

        for (int i = 0; i < word.size(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                Node *newnode = new Node();
                node->put(word[i], newnode);
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    int search(vector<int> word)
    {

        int ans = 0;
        Node *node = head;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->containsKey(word[i]))
                return ans;
            ans++;

            node = node->get(word[i]);
        }
        return ans;
    }
};

int main()
{
    vector<int> x;
    Trie *trie = new Trie(); // initialize
    trie->insert(x);         ////insert vector of x

    trie->search(x); /////search in vector of x
}
