#include <iostream>

using namespace std;

// Find n critical value without looping
void critical_value_smart(pair<int, int> first, pair<int, int> second)
{
    cout << "First equation is " << first.first << "n + " << first.second << endl;
    cout << "Second equation is " << second.first << "n + " << second.second << endl;

    int value = (second.second - first.second) / (first.first - second.first);
    if (value <= 0)
    {
        if (first.first > second.first)
        {
            cout << "Second equation is always faster" << endl;
        }
        else
        {
            cout << "First equation is always faster" << endl;
        }
    }
    else
    {
        cout << "First equation is faster until n is greater then " << value << endl;
    }
}

void critical_value(pair<int, int> first, pair<int, int> second)
{
    int firstVal1 = first.first * 1 + first.second;
    int firstVal2 = second.first * 1 + second.second;
    size_t n = 2;
    while (true)
    {
        size_t val1 = first.first * n + first.second;
        size_t val2 = second.first * n + second.second;

        if (firstVal1 > firstVal2 && val1 < val2)
        {
            cout << "Second equation is faster until n is greater then " << n - 1 << endl;
            break;
        }
        else if (firstVal1 < firstVal2 && val1 > val2)
        {
            cout << "First equation is faster until n is greater then " << n - 1 << endl;
            break;
        }
        n++;
    }
}

int main()
{
    critical_value(pair<int, int>(5, 10), pair<int, int>(1, 50));
    critical_value(pair<int, int>(1, 50), pair<int, int>(2, 0));
    return 0;
}