#include <bits/stdc++.h>

using namespace std;

long long strhash(string s)
{
    long long p = 1;
    long long sum = 0;
    for (int i = 0; i < s.length(); i++)
    {
        sum += ((s[i] - 'a' + 1) * p);
        p *= 31;
        p %= 1000000007;
    }
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;
    set<long long> hashes;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        hashes.insert(strhash(s));
    }
    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        long long tmp = strhash(s);
        long long p = 1;
        bool found = false;
        for (int j = 0; j < s.length(); j++)
        {
            tmp -= ((s[j] - 'a' + 1) * p);
            for (char c = 'a'; c <= 'c'; c++)
            {
                if (c == s[j])
                {
                    continue;
                }
                tmp += ((c - 'a' + 1) * p);
                if (hashes.find(tmp) != hashes.end())
                {
                    found = true;
                    break;
                }
                tmp -= ((c - 'a' + 1) * p);
            }
            tmp += ((s[j] - 'a' + 1) * p);
            p *= 31;
            p %= 1000000007;
        }
        if (found)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}