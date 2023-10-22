#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n, currentelement, q1, q2start, q2end;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        cin >> currentelement;
        v.push_back(currentelement);
    }
    cin >> q1 >> q2start >> q2end;

    v.erase(v.begin() + q1 - 1);
    v.erase(v.begin() + q2start - 1, v.begin() + q2end - 1);
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }

    return 0;
}
