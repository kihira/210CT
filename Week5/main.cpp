#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template <typename N>
struct elem {
    N value;
    shared_ptr<elem> next;
};

template <typename N>
using ElemPtr = shared_ptr<elem<N>>;

template <typename N>
class CircularLinkedList
{
public:
    ElemPtr<N> first;
    ElemPtr<N> last;
    void remove(ElemPtr<N> e)
    {
        ElemPtr<N> curr = first;
        while (true)
        {
            if (curr->next == e)
            {
                ElemPtr<N> next = curr->next->next; // need to copy to prevent issues
                curr->next = next;
                break;
            }
            curr = curr->next;
        }
    }
    CircularLinkedList(vector<N> input)
    {
        ElemPtr<N> start(new elem<N>);
        start->value = input[0];
        start->next = this->first;
        this->first = start;
        this->last = this->first;
        for (int i = 1; i < input.size(); i++)
        {
            ElemPtr<N> in(new elem<N>);
            in->value = input[i];
            in->next = this->first;
            this->last->next = in;
            this->last = in;
        }
    }
};

int main()
{
    //vector<string> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie", "Bob", "Joseph"};
    vector<string> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie"};
    CircularLinkedList<string> list(a);

    ElemPtr<string> value = list.last;
    for (int i = 0; i < a.size()-1; i++)
    {
        for (int j = 0; j < a.size()-1; j++) // Loop around until the next one is found
        {
            value = value->next;
        }
        list.remove(value->next);
    }
    cout << value->value << endl; // This is the final one remaining
}