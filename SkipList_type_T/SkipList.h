#pragma once
#include "SLNode.h"
#include <vector>
#include <string>
#include <iostream>

// Based on pseudocode from
// https://brilliant.org/wiki/skip-lists/
// https://www.baeldung.com/cs/skip-lists
// and linked list base provided in Priority Queue lab

template <typename T>
class SkipList{
private:
    Node<T> head;
    unsigned int width;
    unsigned int height;

    // Insertion Helpers
    bool flip();
    unsigned int promoLevel(Node<T>* newNode);
public:
    SkipList();
    SkipList(T data);
    SkipList(std::vector<T> vec);
    ~SkipList();

    Node<T>* insert(T data);
    Node<T>* search(T data);
    void remove(T data);
    unsigned int size();
    std::string to_string();
    std::string full_print();
};

template <typename T>
SkipList<T>::SkipList(){
    width = 0;
    height = 0;
}

template <typename T>
SkipList<T>::SkipList(T data){
    head.nexts.push_back(new Node<T>(data));
    width = 1;
    height = 1;
}

template <typename T>
SkipList<T>::SkipList(std::vector<T> vec){
    width = vec.size();
    height = 0;
    if(width != 0){
        head.nexts.push_back(nullptr);
        height = 1;
        for(int i = 0; i < vec.size(); i++){
            insert(vec.at(i));
        }
    }
}

template <typename T>
SkipList<T>::~SkipList(){
    delete this->head.nexts.front();
    this->head.nexts.clear();
}

// Flips a coin, 50/50 chance for T/F
template <class T>
bool SkipList<T>::flip(){
    if((rand() % 2) == 0){return true;}
    else{return false;}
}

// Finds what level the new node should be promoted to
template <typename T>
unsigned int SkipList<T>::promoLevel(Node<T>* newNode) {
    unsigned int lvl = 1;
    while(flip()){
        lvl++;
        newNode->nexts.push_back(nullptr);
    }
    while(this->height < lvl){
        head.nexts.push_back(nullptr);
        height++;
    }
    return lvl;
}

template <typename T>
Node<T>* SkipList<T>::insert(T data){
    //std::cout<< "Inserting: " << data << "\n";
    Node<T>* newNode = new Node<T>(data);
    unsigned int nNodeLvl = promoLevel(newNode);
    Node<T>* p = &head;
    Node<T>* n;
    // Works down the layers iteratively
    for(unsigned int curLvl=this->height; curLvl>0; curLvl--){
        n = p->nexts.at(curLvl-1);
        // Works right until next node's value is larger
        while(n!=nullptr && data >= n->data){
            p = n;
            n = p->nexts.at(curLvl-1);
            //std::cout<< "Moved right to " << p->data << "\n";
        }
        if(nNodeLvl >= curLvl){
            p->nexts.at(curLvl-1) = newNode;
            newNode->nexts.at(curLvl-1) = n;
        }
    }
    this->width++;
    //std::cout<< "{ " << to_string() << "}" <<std::endl;
    return newNode;
}

// Returns pointer to Node holding 'data', or nullptr if that doesn't exist
template <typename T>
Node<T>* SkipList<T>::search(T data){
    if(this->head.nexts.empty()){return nullptr;}
    Node<T>* p = &head;
    Node<T>* n;
    // Works down the layers iteratively
    for(unsigned int curLvl=this->height; curLvl>0; curLvl--){
        n = p->nexts.at(curLvl-1);
        // Searches right until next node's value is larger
        while(n!=nullptr && n->data < data){
            p = n;
            n = p->nexts.at(curLvl-1);
        }
    }
    // p now points to a node containing the highest value below 'data'
    // Checks if next node contains 'data', if not, it's not in the list
    if( (n != nullptr) && (n->data == data) ){
        return n;
    }else{
        return nullptr;
    }
}

// Removes first node containing 'data',
template <typename T>
void SkipList<T>::remove(T data){
    unsigned int targetHeight;
    Node<T>* target = search(data);
    if(target != nullptr){
        // For edge case where two nodes have same data and the second is "taller"
        targetHeight = target->nexts.size();
    }else{return;}
    Node<T>* p = &head;
    Node<T>* n;
    for(unsigned int curLvl=targetHeight; curLvl>0; curLvl--){
        n = p->nexts.at(curLvl-1);
        while(n!=nullptr && n->data < data){
            p = n;
            n = p->nexts.at(curLvl-1);
        }
        // If pointing to 'data', point through to next
        if( (n != nullptr) && (n->data == data) ) {
            p->nexts.at(curLvl-1) = n->nexts.at(curLvl-1);
        }
    }
    delete target;
    width--;
}

template <typename T>
unsigned int SkipList<T>::size(){
    return this->width;
}

template <class T>
std::string SkipList<T>::to_string(){
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}
    Node<T>* tmp = this->head.nexts.at(0);
    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->nexts.at(0);
    }

    return stringified;
}

template <>
std::string SkipList<std::string>::to_string(){
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}
    Node<std::string>* tmp = this->head.nexts.at(0);
    while(tmp != nullptr){
        stringified += tmp->data + " ";
        tmp = tmp->nexts.at(0);
    }

    return stringified;
}

template <typename T>
std::string SkipList<T>::full_print() {
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}

    for(int i=0; i<this->height-1; i++){
        stringified += "---";
    }
    stringified += "--\n";

    Node<T>* c = head.nexts.at(0);
    while(c!=nullptr) {
        for (int i = 0; i < c->nexts.size(); i++) {
            stringified += std::to_string(c->data) + " ";
        }
        for (int i = 0; i < (this->height - c->nexts.size()); i++) {
            stringified += " | ";
        }
        stringified += "\n";
        c = c->nexts.at(0);
    }

    for(int i=0; i<this->height-1; i++){
        stringified += "---";
    }
    stringified += "--";

    return stringified;
}

template <>
std::string SkipList<std::string>::full_print() {
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}

    for(int i=0; i<this->height-1; i++){
        stringified += "---";
    }
    stringified += "--\n";

    Node<std::string>* c = head.nexts.at(0);
    while(c!=nullptr) {
        for (int i = 0; i < c->nexts.size(); i++) {
            stringified += c->data + " ";
        }
        for (int i = 0; i < (this->height - c->nexts.size()); i++) {
            stringified += " | ";
        }
        stringified += "\n";
        c = c->nexts.at(0);
    }

    for(int i=0; i<this->height-1; i++){
        stringified += "---";
    }
    stringified += "--";

    return stringified;
}
