#include <iostream>
#include <vector>

using namespace std;

#define CUBES 10
#define EDGE_MAX 10;
#define COLOUR_MAX 10;

struct cube
{
    int edge = 0;
    int colour = 0;
} blank;

vector<cube> merge(vector<cube> cubes1, vector<cube> cubes2)
{
    vector<cube> c;

    while (cubes1.size() != 0 && cubes2.size() != 0)
    {

        if (cubes1[0].edge > cubes2[0].edge)
        {
            c.push_back(cubes2[0]);
            cubes2.erase(cubes2.begin()); // remove first element
        }
        else
        {
            c.push_back(cubes1[0]);
            cubes1.erase(cubes1.begin()); // remove first element
        }
    }

    // Cleanup remaining elements
    while (cubes1.size() != 0)
    {
        c.push_back(cubes1[0]);
        cubes1.erase(cubes1.begin());
    }

    while (cubes2.size() != 0)
    {
        c.push_back(cubes2[0]);
        cubes2.erase(cubes2.begin());
    }

    return c;
}

vector<cube> merge_sort(vector<cube> cubes)
{
    if (cubes.size() == 1) return cubes;

    vector<cube> l1;
    vector<cube> l2;
    l1.assign(cubes.begin(), cubes.begin() + (cubes.size() / 2));
    l2.assign(cubes.begin() + (cubes.size() / 2), cubes.end());

    l1 = merge_sort(l1);
    l2 = merge_sort(l2);

    return merge(l1, l2);
}

int main()
{
    cout << "Advanced Task 1" << endl;
    vector<cube> cubes;
    srand(time(NULL));
    for (int i = 0; i < CUBES; i++)
    {
        cube c;
        c.edge = rand() % EDGE_MAX + 1;
        c.colour = rand() % COLOUR_MAX;
        cubes.push_back(c);
        cout << c.edge << ", ";
    }
    cout << endl;

    vector<cube> sorted = merge_sort(cubes);
    vector<cube> final;
    int prevEdge = -1;
    int prevCol = -1;
    for (int i = 0; i < sorted.size(); i++)
    {
        cube c = sorted[i];
        if (c.edge != prevEdge && c.colour != prevCol)
        {
            prevEdge = c.edge;
            prevCol = c.colour;
            final.push_back(c);
        }
    }

    for (int i = final.size() - 1; i >= 0; i--)
    {
        cube c = final[i];
        cout << "E: " << c.edge << " C: " << c.colour << endl;
    }

    return 0;
}