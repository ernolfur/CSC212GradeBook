#include "skip_list.h"
#include <iostream>

// Based on pseudocode from
// https://brilliant.org/wiki/skip-lists/
// https://www.baeldung.com/cs/skip-lists
// and linked list base provided in Priority Queue lab

SkipList::SkipList(){
    this->width = 0;
    this->height = 0;
}

SkipList::SkipList(int data){
    this->head.nexts.push_back(new Node(data));
    this->width = 1;
    this->height = 1;
}

SkipList::SkipList(std::vector<int> vec){
    this->width = vec.size();
    if(width == 0){
        this->height = 0;
    }else{
        this->head.nexts.push_back(nullptr);
        this->height = 1;
        for(int i = 0; i < vec.size(); i++){
            insert(vec.at(i));
        }
    }
}

SkipList::~SkipList(){
    delete this->head.nexts.front();
    this->head.nexts.clear();
}

// Flips a coin, 50/50 chance for T/F
bool SkipList::flip(){
    if((rand() % 2) == 0){return true;}
    else{return false;}
}

// Finds what level the new node should be promoted to
unsigned int SkipList::promoLevel(Node* newNode) {
    unsigned int lvl = 1;
    while(flip()){
        lvl++;
        newNode->nexts.push_back(nullptr);
    }
    //expands head pointer array as necessary
    while(lvl > height){
        this->head.nexts.push_back(nullptr);
        height++;
    }
    return lvl;
}

void SkipList::insert(int data){
    Node* newNode = new Node(data);
    unsigned int nNodeLvl = promoLevel(newNode);
    Node* p = &head;
    Node* n;
    // Works down the layers iteratively
    for(unsigned int curLvl=height; curLvl>0; curLvl--){
        n = p->nexts.at(curLvl-1);
        // Works right until next node's value is larger
        while(n!=nullptr && data >= n->data){
            p = n;
            n = p->nexts.at(curLvl-1);
        }
        if(nNodeLvl >= curLvl){
            p->nexts.at(curLvl-1) = newNode;
            newNode->nexts.at(curLvl-1) = n;
        }
    }
    width++;
}

// Returns pointer to Node holding 'data', or nullptr if that doesn't exist
Node* SkipList::search(int data){
    if(this->head.nexts.empty()){return nullptr;}
    Node* p = &head;
    Node* n;
    // Works down the layers iteratively
    for(unsigned int curLvl=height; curLvl>0; curLvl--){
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
void SkipList::remove(int data){
    unsigned int targetHeight;
    Node* target = search(data);
    if(target != nullptr){
       // For edge case where two nodes have same data and the second is "taller"
       targetHeight = target->nexts.size();
    }else{return;}
    Node* p = &head;
    Node* n;
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
}

unsigned int SkipList::size(){
    return this->width;
}

std::string SkipList::to_string(){
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}
    Node* tmp = this->head.nexts.at(0);
    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->nexts.at(0);
    }

    return stringified;
}


std::string SkipList::full_print() {
    std::string stringified;
    if(this->head.nexts.empty()){return stringified;}

    for(int i=0; i<height-1; i++){
        stringified += "---";
    }
    stringified += "--\n";

    Node* c = head.nexts.at(0);
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

    for(int i=0; i<height-1; i++){
        stringified += "---";
    }
    stringified += "--";

    return stringified;
}
