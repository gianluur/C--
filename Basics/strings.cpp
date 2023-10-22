#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a, b;
    cin >> a >> " " >> b;
    int alen = a.length(), blen = b.length();
    string concat = a + b;
    char a1 = a[0], b1 = b[0];
    string swapped = b1 + a.substr(1, alen - 1) + " " + a1 + b.substr(1, blen - 1);
    cout << alen << " " << blen << endl
         << concat << endl
         << swapped;
}