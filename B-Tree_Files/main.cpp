#include "B-tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::string filename;
    std::cout << "Enter CSV file name: ";
    std::getline(std::cin, filename);

    BTree tree(3);  // A B-Tree with min degree 3
    tree.readCSVAndPopulateBTree(filename);

    do {
        std::cout << "Enter CSV file name: ";
        std::getline(std::cin, filename);
        
        tree.readCSVAndPopulateBTree(filename);
        
    } while (!tree.root); 

    std::string command;
    std::cout << "Enter command ('sort', 'bonus', 'append', 'exit'): ";
    std::getline(std::cin, command);

    while (command != "exit") {
        if (command == "sort") {
            std::cout << "Sorted Grades:\n";
            tree.traverse(false);  // false to not show bonuses
        } else if (command == "bonus") {
            std::cout << "Students eligible for attendance bonus:\n";
            tree.traverse(true);  // true to only show students with bonuses
        } else if (command == "append") {
            tree.appendStudentToCSV(filename);
            tree = BTree(3);  // Reinitialize the tree
            tree.readCSVAndPopulateBTree(filename);  // Re-populate the tree
            std::cout << "Student information successfully added";
        } else {
            std::cout << "Unknown command. Try again.\n";
        }
        std::cout << "\nEnter command ('sort', 'bonus', 'append', 'exit'): ";
        std::getline(std::cin, command);
    }

    return 0;
}

