#include <iostream>
#include <vector>

using namespace std;

template <typename N>
struct elem {
    N value;
    elem *next;
};

template <typename N>
class CircularLinkedList
{
public:
    elem<N>* first;
    elem<N>* last;
    void remove(elem<N>* e)
    {
        elem<N>* curr = first;
        while (true)
        {
            if (curr->next == e)
            {
                elem<N>* next = curr->next->next; // need to copy to prevent issues
                curr->next = next;
                delete e;
                break;
            }
            curr = curr->next;
        }
    }
    CircularLinkedList(vector<N> input)
    {
        this->first = new elem<N>;
        this->first->value = input[0];
        this->first->next = this->first;
        this->last = this->first;
        for (int i = 1; i < input.size(); i++)
        {
            elem<N> *in = new elem<N>;
            in->value = input[i];
            in->next = this->first;
            this->last->next = in;
            this->last = in;
        }
    }
    ~CircularLinkedList()
    {
//        elem<N>* curr = this->first;
//        while (true)
//        {
//            elem<N>* temp = curr->next;
//            delete curr;
//            curr = temp;
//        }
    }
};

int main()
{
    //vector<string> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie", "Bob", "Joseph"};
    vector<string> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie"};
    CircularLinkedList<string> list(a);

    elem<string>* value = list.last;
    elem<string>* prev = list.last;
    for (int i = 0; i < a.size()-1; i++)
    {
        for (int j = 0; j < a.size()-1; j++) // Loop around until the next one is found
        {
            prev = value;
            value = value->next;
        }
        list.remove(value->next);
    }
    cout << value->value << endl; // This is the final one remaining
}