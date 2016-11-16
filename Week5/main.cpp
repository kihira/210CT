#include <iostream>
#include <array>

using namespace std;

template <typename N>
struct elem {
    N value;
    elem *next;
};

template <typename N, size_t s>
class CircularLinkedList
{
public:
    elem<N> *first;
    elem<N> *last;
//    void remove(elem<N> *e)
//    {
//        elem<N> *curr = first;
//        while (true)
//        {
//            if (curr->next == e)
//            {
//                curr->next = curr->next->next;
//                delete &curr->next;
//                break;
//            }
//            curr = curr->next;
//        }
//        //delete curr;
//    }
    CircularLinkedList(array<N, s> input)
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
//    ~CircularLinkedList()
//    {
//        elem<N>* curr = this->first;
//        while (true)
//        {
//            elem<N>* temp = curr->next;
//            delete curr;
//            curr = temp;
//        }
//    }
};

int main()
{
    //array<string, 7> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie", "Bob", "Joseph"};
    array<string, 5> a = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie"};
    CircularLinkedList<string, 5> list(a);

    elem<string>* value = list.last;
    elem<string>* prev = list.last;
    for (int i = 0; i < a.size()-1; i++)
    {
        for (int j = 0; j < a.size()-1; j++) // Loop around until the next one is found
        {
            prev = value;
            value = value->next;
        }
        elem<string>* temp = value->next;
        list.remove(value->next);
        //value->next = value->next->next; // Then "remove" it from the chain
        delete temp;
    }
    cout << value->value << endl; // This is the final one remaining
}