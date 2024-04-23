#pragma once
#include <vector>

template <typename N>
class Node{
private:
    N key;
    std::vector<Node<N>*> nexts;

    template <typename T>
    friend class SkipList;
public:
   Node();
    // Overloading
    Node(N key);
    Node(N key, Node* next);
    ~Node();
};

// Default constructor
template <typename N>
Node<N>::Node(){
    this->nexts.push_back(nullptr);
}

template <typename N>
Node<N>::Node(N key){
    this->key = key;
    this->nexts.push_back(nullptr);
}

template <typename N>
Node<N>::Node(N key, Node* next){
    this->key = key;
    this->nexts.push_back(next);
}

template <typename N>
Node<N>::~Node(){
    this->nexts.clear();
}
