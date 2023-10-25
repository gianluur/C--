#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countApplesAndOranges(int s, int t, int a, int b, vector<int> apples, vector<int> oranges)
{
    int apple_count = 0, orange_count = 0;

    for (int i = 0; i < apples.size(); i++)
    {
        if (apples[i] + a >= s && apples[i] + a <= t)
        {
            apple_count++;
        }
    }
    for (int i = 0; i < oranges.size(); i++)
    {
        if (oranges[i] + b >= s && oranges[i] + b <= t)
        {
            orange_count++;
        }
    }
    cout << apple_count << endl
         << orange_count << endl;
}

int main()
{
    countApplesAndOranges(7, 11, 4, 12, {-2, 2, 1}, {5, -6});
}
