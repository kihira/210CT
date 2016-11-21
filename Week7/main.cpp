#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <queue>

using namespace std;

struct vertice
{
    int value;
    vector<vertice*> vertices;
    // used for tarjans algo for checking for strong connection
    int index = -1;
    int lowlink = -1;
    bool onStack = false;
    vertice(int value) : value(value) {}
};

class Graph
{
private:
    map<int, vertice*> vertices; // can use default map instead of unordered as a sorted map is probably good
public:
    vertice* addNode(int value, vertice* n) { return addNode(value, vector<vertice*>(1, n)); }
    vertice* addNode(int value, vector<vertice*> adjacent = vector<vertice*>())
    {
        if (vertices.count(value) > 0)
        {
            throw invalid_argument("Vertice already exists with value");
        }
        vertice* n = new vertice(value);
        n->vertices = adjacent;
        for (vertice* adj : adjacent)
        {
            adj->vertices.push_back(n);
        }

        vertices[value] = n;

        return n;
    }
    bool exists(int value)
    {
        return vertices.count(value) > 0;
    }
    vertice* getNode(int value)
    {
        return vertices[value];
    }
    bool isPath(int v, int w, ofstream& outFile) // recursive search
    {
        vertice* curr = vertices[v];
        vector<vertice*> verticesToSearch;

        outFile << v << endl;

        for (vertice* n : curr->vertices)
        {
            if (n->value == w)
            {
                return true;
            }
            else if (n->vertices.size() > 0)
            {
                verticesToSearch.push_back(n); // scan over all links first to see if we have a direct connection
            }
        }
        for (vertice* n : verticesToSearch)
        {
            return isPath(n->value, w, outFile); // now we know we don't have a direct connection, search links
        }

        return false;
    }
    // uses tarjans algorithm which is O(v + e)
    // tarjans algo
    bool strongconnect(vertice* v, int* index, queue<vertice*>* S)
    {
        v->index = *index;
        v->lowlink = *index;
        index = index + 1;
        S->push(v);
        v->onStack = true;

        for (vertice* edge : v->vertices)
        {
            if (edge->index == -1)
            {
                strongconnect(edge, index, S);
                v->lowlink = min(v->lowlink, edge->lowlink);
            }
            else if (edge->onStack)
            {
                edge->lowlink = min(v->lowlink, edge->index);
            }
        }

        if (v->lowlink == v->index)
        {
            vector<vertice*> scc;
            vertice* w;
            do
            {
                w = S->front();
                S->pop();
                w->onStack = false;
                scc.push_back(w);
            }
            while(w != v);
            for (vertice* i : scc)
            {
                cout << i->value << endl;
            }
            return true;
        }
        return false;
    }
    bool isConnected() // returns true is sccCount is 0 as everything is one component
    {
        int* index = new int(0);
        queue<vertice*>* S = new queue<vertice*>();
        int sccCount = 0; // strongly connected components count
        for (auto v : vertices)
        {
            if (v.second->index == -1)
            {
                if (strongconnect(v.second, index, S)) sccCount++;
            }
        }
        delete index;
        delete S;
        cout << (sccCount == 0 ? "yes" : "no") << endl;
        return sccCount == 0;
    }
    Graph() {}
    Graph(vector<int> v, vector<pair<int, int>> edges)
    {
        for (int i : v) // setup vertices
        {
            vertices[i] = new vertice(i);
        }
        for (pair<int, int> i : edges) // setup edges
        {
            if (vertices.count(i.first) == 0 || vertices.count(i.second) == 0)
            {
                throw invalid_argument("A vertice specified in edge doesn't exist");
            }
            vertice* first = vertices[i.first];
            vertice* second = vertices[i.second];
            first->vertices.push_back(second);
            second->vertices.push_back(first);
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
    cout << "Advanced Task 1 - Unweighted, Undirected graph" << endl;

    Graph graph({1, 2, 3, 4, 5}, {{1, 2}, {2, 3}, {3, 1}});
    ofstream outFile("search.txt");
    //cout << graph.isPath(3, 1, outFile);
    outFile.close();
    graph.isConnected();
}