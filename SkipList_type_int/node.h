#pragma once

#include <vector>

class Node{
private:
    int data;
    std::vector<Node*> nexts;

    friend class SkipList;
public:
    Node();
    // Overloading
    Node(int data);
    Node(int data, Node* next);
    ~Node();
};
