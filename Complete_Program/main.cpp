#include "B-tree.h"
#include "naive.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


int main() {
    std::string filename;
    std::ifstream testFile;

    // Prompt for valid file name initially
    while (true) {
        std::cout << "Enter CSV file name or 'exit' to quit: ";
        std::getline(std::cin, filename);
        if (filename == "exit") {
            return 0;  // Exit the program if user inputs 'exit'
        }
        testFile.open(filename);
        if (testFile.good()) {
            testFile.close();
            break;  // Exit the loop if the file is found
        } else {
            std::cout << "File not found. Please enter a valid CSV file name.\n";
            testFile.close();  // Important to close the ifstream if an attempt fails
        }
    }

    Naive naive(filename);  // Initialize Naive search with the filename
    BTree tree(3);  // Initialize a B-Tree with min degree 3
    tree.readCSVAndPopulateBTree(filename);  // Populate the B-Tree with data from the CSV

    std::string command;
    std::cout << "Enter command ('search_name', 'search_grade', 'sort', 'bonus', 'append', 'delete', 'exit'): ";
    std::getline(std::cin, command);

    while (command != "exit") {
        if (command == "search_name") {
            std::string name_pattern;
            std::cout << "Enter name pattern to search: ";
            std::getline(std::cin, name_pattern);
            naive.searchName(name_pattern);
        } else if (command == "search_grade") {
            std::string grade_pattern;
            std::cout << "Enter grade pattern to search: ";
            std::getline(std::cin, grade_pattern);
            naive.searchGrade(grade_pattern);
        } else if (command == "sort") {
            std::cout << "Sorted Grades:\n";
            tree.traverse(false);  // Argument false to not show bonuses
        } else if (command == "bonus") {
            std::cout << "Students eligible for attendance bonus:\n";
            tree.traverse(true);  // Argument true to show only students with bonuses
        } else if (command == "append") {
            tree.appendStudentToCSV(filename);  // Append student to CSV and B-Tree
            // Re-load the data into Naive and BTree after appending
            naive = Naive(filename);  // Reinitialize Naive with the current filename
            tree = BTree(3);  // Reinitialize the B-Tree
            tree.readCSVAndPopulateBTree(filename);  // Re-populate the B-Tree
            std::cout << "Student information successfully added and updated in the search index.\n";
        } else if (command == "delete") {
            std::string name_pattern;
            std::cout << "Enter name pattern to search: ";
            std::getline(std::cin, name_pattern);
            naive.deleteLine(name_pattern, filename);
        }
        else {
            std::cout << "Unknown command. Please try again.\n";
        }

        std::cout << "Enter next command ('search_name', 'search_grade', 'sort', 'bonus', 'append', 'delete', 'exit'): ";
        std::getline(std::cin, command);
    }

    return 0;
}