#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> coord;

void task1()
{
    float a, b, c, d;
    cout << "a:";
    cin >> a;
    cout << "b:";
    cin >> b;
    cout << "c:";
    cin >> c;
    cout << "d:";
    cin >> d;

    cout << (a/b > c/d ? a/b : c/d) << endl;

}

coord parseCoord(string& input)
{
    int a, b = 0;
    if (int pos = input.find(',') != string::npos)
    {
        a = atoi(input.substr(0, pos).c_str()); // Convert from string to char (c_str) then atoi converts to int
        b = atoi(input.substr(pos+1, input.length()-1).c_str());
    }
    return coord(a, b);
}

void task2()
{
    string tempIn;
    coord a, b, c, p;

    cout << "Input coordinates in the format a,b" << endl
         << "A: ";
    cin >> tempIn;
    a = parseCoord(tempIn);

    cout << "B: ";
    cin >> tempIn;
    b = parseCoord(tempIn);

    cout << "C: ";
    cin >> tempIn;
    c = parseCoord(tempIn);

    cout << "P: ";
    cin >> tempIn;
    p = parseCoord(tempIn);

    cout << (p.first > a.first && p.first > b.first && p.first > c.first ? "P is to the left" : "P is to the right") << endl;
    cout << (p.second > a.second && p.second > b.second && p.second > c.second ? "P is above" : "P is below");
}

void task3()
{
    int x;
    cout << "x: ";
    cin >> x;

    cout << (x<-2?(x*x)+(4*x)+4:(x==0?0:(x*x)+(5*x)));
}
