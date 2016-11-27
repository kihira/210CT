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
};

vector<cube> merge(vector<cube> cubes1, vector<cube> cubes2)
{
    vector<cube> result;
    result.reserve(cubes1.size() + cubes2.size()); // Reserve memory for total size for performance improvements on large merges

    while (cubes1.size() != 0 && cubes2.size() != 0) // Keep running as long as there are elements in both
    {

        if (cubes1[0].edge > cubes2[0].edge)
        {
            result.push_back(cubes2[0]);
            cubes2.erase(cubes2.begin()); // remove first element
        }
        else
        {
            result.push_back(cubes1[0]);
            cubes1.erase(cubes1.begin()); // remove first element
        }
    }

    // Split up remaining elements
    while (cubes1.size() != 0)
    {
        result.push_back(cubes1[0]);
        cubes1.erase(cubes1.begin());
    }

    while (cubes2.size() != 0)
    {
        result.push_back(cubes2[0]);
        cubes2.erase(cubes2.begin());
    }

    return result;
}

vector<cube> merge_sort(vector<cube> cubes)
{
    if (cubes.size() == 1) return cubes;

    vector<cube> first;
    vector<cube> second;
    first.assign(cubes.begin(), cubes.begin() + (cubes.size() / 2)); // Take values from left of midpoint
    second.assign(cubes.begin() + (cubes.size() / 2), cubes.end()); // Take values from right of midpoint (inclusive)

    // Keep splitting until vectors are just size 1
    first = merge_sort(first);
    second = merge_sort(second);

    return merge(first, second);
}

int main()
{
    cout << "Advanced Task 1 - Cube sorting" << endl;
    vector<cube> cubes;
    srand(time(NULL));

    cout << "Cubes (Edge, Colour):" << endl;
    for (int i = 0; i < CUBES; i++)
    {
        cube c;
        c.edge = rand() % EDGE_MAX + 1;
        c.colour = rand() % COLOUR_MAX;
        cubes.push_back(c);
        cout << "(" << c.edge << ", " << c.colour << ") ";
    }
    cout << endl << endl;

    vector<cube> sorted = merge_sort(cubes);
    vector<cube> final;
    int prevEdge = -1;
    int prevCol = -1;
    for (int i = 0; i < sorted.size(); i++) // remove cubes that cannot be used
    {
        cube c = sorted[i];
        if (c.edge != prevEdge && c.colour != prevCol)
        {
            prevEdge = c.edge;
            prevCol = c.colour;
            final.push_back(c);
        }
    }

    cout << "Tower (smallest on top)" << endl;
    for (cube c : final)
    {
        cout << "E: " << c.edge << " C: " << c.colour << endl;
    }

    return 0;
}