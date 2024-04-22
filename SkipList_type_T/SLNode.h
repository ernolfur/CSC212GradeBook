#pragma once
#include <vector>

template <typename N>
class Node{
private:
    N data;
    std::vector<Node<N>*> nexts;

    template <typename T>
    friend class SkipList;
public:
    Node();
    // Overloading
    Node(N data);
    Node(N data, Node* next);
    ~Node();
};

// Default constructor
template <typename N>
Node<N>::Node(){
    this->nexts.push_back(nullptr);
}

template <typename N>
Node<N>::Node(N data){
    this->data = data;
    this->nexts.push_back(nullptr);
}

template <typename N>
Node<N>::Node(N data, Node* next){
    this->data = data;
    this->nexts.push_back(next);
}

template <typename N>
Node<N>::~Node(){
    this->nexts.clear();
}
