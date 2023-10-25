#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int n, m, q, target;
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        v.push_back(m);
    }
    for (int i = 0; i < q; i++)
    {
        cin >> target;
        vector<int>::iterator it = lower_bound(v.begin(), v.end(), target);
        if (*it != target)
        {
            cout << "Yes " << (it - v.begin() + 1) << endl;
        }
        else
        {
            cout << "No " << (it - v.begin() + 1) << endl;
        }
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
