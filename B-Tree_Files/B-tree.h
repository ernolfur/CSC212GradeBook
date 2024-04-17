#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Student {
    std::string name;
    int labGrade1, labGrade2, assignmentGrade1, assignmentGrade2;
    bool attendance;

    float averageGrade() const {
        return (labGrade1 + labGrade2 + assignmentGrade1 + assignmentGrade2) / 4.0f;
    }
};

class BTreeNode {
private:
    int t;
    bool leaf;
    Student *students;
    BTreeNode **C;
    int n;

    friend class BTree;

public:
    BTreeNode(int _t, bool _leaf);
    void traverse(bool showBonusOnly = false);
    void insertNonFull(Student k);
    void splitChild(int i, BTreeNode *y);
};

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int _t);
    void insert(Student k);
    void traverse(bool showBonusOnly = false);

    void appendStudentToCSV(const std::string& filename);
    void readCSVAndPopulateBTree(const std::string &filename);
};
