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
                if (curr->next == first)
                {
                    first = next;
                }
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

void task1()
{
    cout << "Advanced task 1 - Matrix to the kth power" << endl;
    cout << "Enter power to multiply matrix by: " << endl;

    const int dims = 2; // need const as array size is determined at compile time
    int matrix[dims*dims]; // 2x2
    for (int i = 1; i <= dims*dims; i++)
    {
        matrix[i-1] = i;
    }
    int power;
    cin >> power;

    int outMatrix[dims*dims];
    copy(begin(matrix), end(matrix), begin(outMatrix)); // copy data from first matrix
    for (int p = 1; p < power; p++) { // start at 1 otherwise off by 1
        int resultMatrix[dims*dims];
        for (int row = 0; row < dims; row++) {
            for (int colRHS = 0; colRHS < dims; colRHS++) {
                int total = 0;
                for (int col = 0; col < dims; col++) {
                    total += *(matrix + row*dims + col) * *(outMatrix + col*dims + colRHS); // index of row-major matrixes is found via row * ROWS + col but seeing as it's square, just use dim
                }
                resultMatrix[row*dims + colRHS] = total;
            }
        }
        copy(begin(resultMatrix), end(resultMatrix), begin(outMatrix)); // set outMatrix to result of multiplication
    }

    // output resulting matrix
    cout << "Matrix result: " << endl;
    for (int row = 0; row < dims; row++) {
        for (int col = 0; col < dims; col++) {
            printf("%-5i", *(outMatrix + row*dims + col)); // left align, pad 5, integer
        }
        cout << endl;
    }
    cout << endl;
}

void task2()
{
    cout << "Advanced task 2 - Children's elimination game" << endl;
    vector<string> participants = {"Eliot", "Charlie", "Zoe", "Alex", "Sophie"};
    CircularLinkedList<string> list(participants);

    cout << "Participants: ";
    for (int i = 0; i < participants.size(); ++i) {
        cout << participants[i] << (i == participants.size()-1 ? "\n" : ", ");
    }

    ElemPtr<string> value = list.last;
    for (int i = 0; i < participants.size()-1; i++)
    {
        for (int j = 0; j < participants.size()-1; j++) // Loop around until the next one is found
        {
            value = value->next;
        }
        list.remove(value->next);
    }
    cout << "Winner: " << value->value << endl; // This is the final one remaining
}

int main()
{
    task1();
    task2();
}