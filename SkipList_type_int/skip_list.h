#include "node.h"
#include <vector>
#include <string>

// Based on pseudocode from
// https://brilliant.org/wiki/skip-lists/
// https://www.baeldung.com/cs/skip-lists
// and linked list base provided in Priority Queue lab

class SkipList{
private:
    Node head;
    unsigned int width;
    unsigned int height;

    // Insertion Helpers
    bool flip();
    unsigned int promoLevel(Node* newNode);
public:
    SkipList(); // this->heads = nullptr;
    SkipList(int data);
    SkipList(std::vector<int> vec);
    ~SkipList();

    void insert(int data);
    Node* search(int data);
    void remove(int data);
    unsigned int size();
    std::string to_string();
    std::string full_print();
};
