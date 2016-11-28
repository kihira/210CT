#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <queue>

using namespace std;

struct vertice
{
    int value;
    vector<vertice*> edges;
    // used for tarjans algo for checking for strong connection
    int index = -1;
    int lowlink = -1;
    bool inStack = false;
    vertice(int value) : value(value) {}
};

class Graph
{
private:
    map<int, vertice*> vertices; // can use default map instead of unordered as a sorted map is probably good
public:
    vertice* addVertice(int value, vertice *n) { return addVertice(value, vector<vertice *>(1, n)); }
    vertice* addVertice(int value, vector<vertice *> edges = vector<vertice *>())
    {
        if (this->vertices.count(value) > 0)
        {
            throw invalid_argument("Vertice already exists with value");
        }
        vertice* n = new vertice(value);
        n->edges = edges;
        for (vertice* adj : edges)
        {
            adj->edges.push_back(n);
        }

        this->vertices[value] = n;

        return n;
    }
    bool exists(int value)
    {
        return this->vertices.count(value) > 0;
    }
    vertice* getVertice(int value)
    {
        return this->vertices[value];
    }
    // Can take in vertices as int as we can safely assume each vertex has unique int
    bool isPath(int start, int target, ofstream& outFile) // recursive search
    {
        vertice* curr = this->vertices[start];
        vector<vertice*> verticesToSearch;

        outFile << start << endl;

        for (vertice* v : curr->edges)
        {
            if (v->value == target)
            {
                return true;
            }
            else if (v->edges.size() > 0)
            {
                verticesToSearch.push_back(v); // scan over all links start to see if we have a direct connection
            }
        }
        for (vertice* n : verticesToSearch)
        {
            return isPath(n->value, target, outFile); // now we know we don't have a direct connection, search links
        }

        return false;
    }
    // uses tarjans algorithm which is O(vertices + edges)
    bool strong_connect(vertice *curr, int *index, queue<vertice *> *stack)
    {
        curr->index = *index;
        curr->lowlink = *index;
        index = index + 1;
        stack->push(curr);
        curr->inStack = true;

        for (vertice* edge : curr->edges)
        {
            if (edge->index == -1) // Haven't checked this vertice yet so check
            {
                strong_connect(edge, index, stack);
                curr->lowlink = min(curr->lowlink, edge->lowlink);
            }
            else if (edge->inStack)
            {
                curr->lowlink = min(curr->lowlink, edge->index); // Check whether the edge is our new "base"
            }
        }

        // Base vertice so need to remove the stuff we have checked from the stack so we can start a new strongly connected component
        if (curr->lowlink == curr->index)
        {
            vertice* v;
            do
            {
                v = stack->front();
                stack->pop();
                v->inStack = false;
            }
            while(v != curr); // need do-while so we at least evaluate front of the queue (in case of 1 size components)
            return true;
        }
        return false;
    }
    // breaks style convention to fit in with coursework requirements
    bool isConnected()
    {
        // Using pointers to help prevent class variables as we can just pass pointers around
        int* index = new int(0);
        queue<vertice*>* stack = new queue<vertice*>();
        int sccCount = 0; // strongly connected components count
        for (auto v : vertices)
        {
            if (v.second->index == -1)
            {
                if (strong_connect(v.second, index, stack)) sccCount++;
            }
        }
        delete index;
        delete stack;
        cout << (sccCount == 0 ? "yes" : "no") << endl;
        return sccCount == 0; // sccCount is 0 when everything is in one component
    }
    Graph() {}
    Graph(vector<int> vertices, vector<pair<int, int>> edges)
    {
        for (int i : vertices) // setup vertices
        {
            this->vertices[i] = new vertice(i);
        }
        for (pair<int, int> edge : edges) // setup edges
        {
            if (this->vertices.count(edge.first) == 0 || this->vertices.count(edge.second) == 0)
            {
                throw invalid_argument("A vertice specified in edge doesn't exist");
            }
            vertice* first = this->vertices[edge.first];
            vertice* second = this->vertices[edge.second];
            first->edges.push_back(second);
            second->edges.push_back(first);
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
    cout << "Advanced Task 1 - Unweighted, Undirected graph" << endl << endl;

    Graph graph({1, 2, 3, 4, 5}, {{1, 2}, {2, 3}, {3, 1}});

    cout << "Checking for a path" << endl;
    ofstream outFile("search.txt");
    int first, second;

    cout << "First node: ";
    cin >> first;
    cout << "Second node: ";
    cin >> second;

    cout << (graph.isPath(first, second, outFile) ? "Path found" : "No path found") << endl << endl;
    outFile.close();

    cout << "Is graph strongly connected? ";
    graph.isConnected();
}