#include "B-tree.h"

BTreeNode::BTreeNode(int t1, bool leaf1) : t(t1), leaf(leaf1), n(0) {
    students = new Student[2*t-1];
    C = new BTreeNode *[2*t];
}

void BTreeNode::traverse(bool showBonusOnly) {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse(showBonusOnly);
        if (!showBonusOnly || students[i].attendance) {
            std::cout << students[i].name << ": " << students[i].averageGrade();
            if (students[i].attendance)
                std::cout << " (Bonus)";
            std::cout << std::endl;
        }
    }
    if (!leaf)
        C[i]->traverse(showBonusOnly);
}

void BTreeNode::insertNonFull(Student k) {
    int i = n-1;
    if (leaf) {
        while (i >= 0 && students[i].averageGrade() > k.averageGrade()) {
            students[i+1] = students[i];
            i--;
        }
        students[i+1] = k;
        n++;
    } else {
        while (i >= 0 && students[i].averageGrade() > k.averageGrade())
            i--;
        if (C[i+1]->n == 2*t-1) {
            splitChild(i+1, C[i+1]);
            if (students[i+1].averageGrade() < k.averageGrade())
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++)
        z->students[j] = y->students[j+t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        students[j+1] = students[j];
    students[i] = y->students[t-1];
    n++;
}

BTree::BTree(int t1) : t(t1), root(nullptr) {}

void BTree::insert(Student k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->students[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2*t-1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->students[0].averageGrade() < k.averageGrade())
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTree::traverse(bool showBonusOnly) {
    if (root != nullptr) root->traverse(showBonusOnly);
}

void BTree::appendStudentToCSV(const std::string& filename) {
    std::string name;
    int labGrade1, labGrade2, assignmentGrade1, assignmentGrade2;
    std::string attendance;
    std::cout << "Enter student's name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Lab Grade 1: ";
    std::cin >> labGrade1;
    std::cout << "Enter Lab Grade 2: ";
    std::cin >> labGrade2;
    std::cout << "Enter Assignment Grade 1: ";
    std::cin >> assignmentGrade1;
    std::cout << "Enter Assignment Grade 2: ";
    std::cin >> assignmentGrade2;
    std::cin.ignore();
    std::cout << "Attendance (Yes/No): ";
    std::getline(std::cin, attendance);

    std::ofstream outFile(filename, std::ios::app);
    outFile << "\"" << name << "\"," << labGrade1 << "," << labGrade2 << ","
            << assignmentGrade1 << "," << assignmentGrade2 << ",\"" << attendance << "\"\n";
    outFile.close();
}

void BTree::readCSVAndPopulateBTree(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line, word;
    std::vector<std::string> row;
    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        row.clear();
        while (getline(ss, word, ',')) {
            row.push_back(word);
        }
        Student stud;
        stud.name = row[0].substr(1, row[0].size() - 2);
        stud.labGrade1 = std::stoi(row[1]);
        stud.labGrade2 = std::stoi(row[2]);
        stud.assignmentGrade1 = std::stoi(row[3]);
        stud.assignmentGrade2 = std::stoi(row[4]);
        stud.attendance = (row[5].substr(1, row[5].size() - 2) == "Yes");
        insert(stud);
    }
    file.close();
}
