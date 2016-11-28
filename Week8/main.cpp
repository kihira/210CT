#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

struct vertice
{
    int value;
    map<vertice*, int> edges;
    vertice(int value) : value(value) {}
};

class Graph
{
private:
    map<int, vertice*> vertices; // can use default map instead of unordered as a sorted map is probably good
public:
    bool operator()(pair<vertice*, int> first, pair<vertice*, int> second)
    {
        return first.second > second.second; // Second value is the priority so sort by that
    }
    // Returns a pair with first being the distance, second being the path
    pair<int, vector<vertice*>> shortest_path(int start, int target)
    {
        typedef pair<vertice*, int> queuePair;
        priority_queue<queuePair, vector<queuePair>, Graph> q; // Specify this class as 3rd parameter to use the operator above for ordering the queue
        map<vertice*, int> weight;
        map<vertice*, vertice*> previous;
        vertice* goal = this->vertices[target];
        vertice* curr;

        q.push({this->vertices[start], 0});
        weight[this->vertices[start]] = 0; // Distance to ourself is 0
        previous[this->vertices[start]] = nullptr;

        while (!q.empty())
        {
            curr = q.top().first;
            q.pop();

            if (curr == goal){
                break; // Don't need to keep searching once we got there
            }

            for (auto edge : curr->edges)
            {
                int dist = weight[curr] + edge.second;
                if (!weight.count(edge.first) || dist < weight[edge.first]) // If this path is shorter, follow this
                {
                    weight[edge.first] = dist;
                    previous[edge.first] = curr;
                    q.push({edge.first, dist});
                }
            }
        }

        curr = goal; // Work backwards to find our path;
        vector<vertice*> path;
        while (true)
        {
            path.push_back(curr);
            curr = previous[curr];
            if (curr == nullptr || curr == previous[curr]) break; // Break once we reach the start position
        }

        // Reverse the path so we go forwards
        reverse(path.begin(), path.end());

        return {weight[goal], path}; // Weight is accumulative so we can just return the final weight for our target
    }
    Graph() {}
    // Edges are in the order <first vertice, second vertice, weight>
    Graph(vector<int> vertices, vector<tuple<int, int, int>> edges)
    {
        for (int i : vertices) // setup vertices
        {
            this->vertices[i] = new vertice(i);
        }
        for (tuple<int, int, int> tuple : edges) // setup edges
        {
            if (this->vertices.count(get<0>(tuple) == 0) || this->vertices.count(get<1>(tuple)) == 0)
            {
                throw invalid_argument("A vertice specified in edge doesn't exist");
            }
            vertice* first = this->vertices[get<0>(tuple)];
            vertice* second = this->vertices[get<1>(tuple)];
            first->edges[second] = get<2>(tuple);
            second->edges[first] = get<2>(tuple);
        }
    }
    ~Graph()
    {
        for (auto value : vertices)
        {
            delete value.second; // cleanup pointers
        }
    }
};

int main()
{
    cout << "Advanced Task 1 - Weighted, Undirected graph" << endl << endl;

    Graph graph({1, 2, 3, 4, 5}, {make_tuple(1, 2, 1), make_tuple(2, 3, 1), make_tuple(1, 4, 3), make_tuple(3, 4, 0), make_tuple(1, 3, 3)});

    int start, target;
    start = 1;
    target = 4;
    stringstream ss;

    pair<int, vector<vertice*>> path = graph.shortest_path(start, target);

    cout << "Distance: " << path.first << endl;
    cout << "Path: ";
    for (vertice* v : path.second)
    {
        ss << " -> " << v->value;
    }
    cout << ss.str().erase(0, 4); // Remove the initial arrow and print out the path
}