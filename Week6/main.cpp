#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Using traditional pointers as shared pointers won't really work unless we keep a reference to parent
struct node
{
    string name;
    int count;
    node *left = NULL;
    node *right = NULL;
    string str()
    {
        stringstream ss;
        ss << name << "(" << count << ") | "
           << "Left Node: " << (left != NULL ? left->name : "None") << " | "
           << "Right Node: " << (right != NULL ? right->name : "None") << endl;
        return ss.str();
    }
    node(string name, int count) : name(name), count(count) {}
};

class BST
{
private:
    node *root = NULL;
    void remove_all(node* n) // used by the destructor
    {
        if (n->left != NULL)
        {
            remove_all(n->left);
        }
        if (n->right != NULL)
        {
            remove_all(n->right);
        }
        delete n;
    }
public:
    node* insert(string name, int count, node* curr = NULL) // recursively insert
    {
        if (root == NULL)
        {
            root = new node(name, count);
        }
        else
        {
            if (curr == NULL)
            {
                curr = root;
            }
            if (name.compare(curr->name) < 0)
            {
                if (curr->left == NULL)
                {
                    curr->left = new node(name, count);
                }
                else
                {
                    insert(name, count, curr->left);
                }
            }
            else
            {
                if (curr->right == NULL)
                {
                    curr->right = new node(name, count);
                }
                else
                {
                    insert(name, count, curr->right);
                }
            }
        }
        return curr;
    }
    bool contains(string name) // Search if it contains the term iteratively
    {
        node *curr = root;
        while (curr != NULL)
        {
            cout << "Current node: " << curr->str();
            int compare = name.compare(curr->name);
            if (compare == 0)
            {
                cout << "Yes" << endl;
                return true;
            }
            if (compare < 0)
            {
                cout << "Heading left" << endl;
                curr = curr->left;
            }
            else
            {
                cout << "Heading right" << endl;
                curr = curr->right;
            }
        }
        cout << "No" << endl;
        return false; // default false
    }
    void pre_order(node *n = NULL) // Pre order output recursively
    {
        if (n == NULL) // assume start
        {
            n = root;
        }
        cout << n->name << ": " << n->count << endl;
        if (n->left != NULL)
        {
            pre_order(n->left);
        }
        if (n->right != NULL)
        {
            pre_order(n->right);
        }
    }
    ~BST()
    {
        remove_all(root); // Cleanup our pointers
    }
};

unordered_map<string, int> count_words(string fileName)
{
    ifstream file;
    unordered_map<string, int> wordCount;
    string word;

    file.open(fileName);
    if (file.is_open())
    {
        while(file >> word)
        {
            if (word[word.length()-1] == ',' || word[word.length()-1] == '.') // ignore punctuation
            {
                word = word.substr(0, word.length()-1);
            }
            transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lower case. Assuming ASCII. Effectively a compressed loop using iterators
            wordCount[word] = (wordCount.find(word) == wordCount.end() ? 0 : wordCount[word]) + 1;
        }
    }
    else
    {
        cout << "Failed to open " << fileName << endl;
    }
    file.close();
    return wordCount;
};

int main(int argc, char *argv[])
{
    const string parse = "--parse";

    BST tree;
    string fileName = argc >= 2 ? argv[1] : "input.txt"; // use specified file if provided

    if (argc == 3 && parse.compare(argv[2]) == 0) // Check if we should parse and count ourselves
    {
        unordered_map<string, int> wordCount = count_words(fileName);
        for (unordered_map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); it++) // one issue, maps are sorted so effectively end up with a very long list. Using unordered as a "workaround"
        {
            tree.insert(it->first, it->second);
        }
    }
    else // otherwise this file is already in the correct format
    {
        ifstream file;
        string name;
        int count;

        file.open(fileName);
        if (file.is_open())
        {
            while(file >> name >> count)
            {
                tree.insert(name, count);
            }
        }
        else
        {
            cout << "Failed to open " << fileName << endl;
        }
        file.close();
    }

    // pre order output
    tree.pre_order();

    // Example of searching
    cout << "Input word to search for: ";
    string in;
    cin >> in;
    cout << "Searching for " << in << endl;
    tree.contains(in);
}