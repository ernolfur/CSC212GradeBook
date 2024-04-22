#include "node.h"

// Default constructor
Node::Node(){
    this->data = 0;
    this->nexts.push_back(nullptr);
}

Node::Node(int data){
    this->data = data;
    this->nexts.push_back(nullptr);
}

Node::Node(int data, Node* next){
    this->data = data;
    this->nexts.push_back(next);
}

Node::~Node(){
    this->nexts.clear();
}