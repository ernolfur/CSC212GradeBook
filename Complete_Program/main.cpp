#include "B-tree.h"
#include "naive.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SkipList.h"

void fillSkipList(SkipList<std::string>* SL, std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line, word;
    getline(file, line);  // skip the header line
    while (getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, word, ',');
        // Puts name into Skip List as new node
        SL->insert(word.substr(1, word.size() - 2));
    }
    file.close();
}

// Function to compute and store grade averages
std::vector<double> computeGradeAverages(const std::string& filename) {
    std::vector<double> grades;
    std::ifstream file(filename);
    std::string line, word;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return grades;  // return empty vector on failure
    }

    getline(file, line);  // skip the header line
    while (getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, word, ',');  // skip the name
        getline(ss, word, ',');  // get the grade
        try {
            double grade = std::stod(word);
            grades.push_back(grade);
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid grade entry: " << word << std::endl;
        }
    }
    file.close();
    return grades;
}

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

    // Compute grade averages at the start
    std::vector<double> gradeAverages = computeGradeAverages(filename);

    Naive naive(filename);  // Initialize Naive search with the filename
    BTree tree(3);  // Initialize a B-Tree with min degree 3
    tree.readCSVAndPopulateBTree(filename);  // Populate the B-Tree with data from the CSV

    std::string command;
    std::cout << "Enter command ('search_name', 'search_grade', 'sort', 'bonus', 'append', 'delete, 'above', 'exit'): ";
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
            gradeAverages = computeGradeAverages(filename); // Updates average grades vector
            std::cout << "Student information successfully added and updated in the search index.\n";
        } else if (command == "delete") {
            std::string name_pattern;
            std::cout << "Enter name pattern to search: ";
            std::getline(std::cin, name_pattern);
            naive.deleteLine(name_pattern, filename);
            gradeAverages = computeGradeAverages(filename); // Updates average grades vector
            std::cout << "Student information successfully deleted.\n";
        } else if (command == "above") {
            SkipList<double> SL(gradeAverages);
            std::string gradeStr;
            std::cout << "Enter a grade to see what percentage of students are above it: ";
            std::getline(std::cin, gradeStr);
            int countAbove = SL.numAfter(std::stoi(gradeStr));
            int total = SL.size();
            int percent = (countAbove * 100) / total;
            std::cout << percent << "% of students have grade averages above " << gradeStr << "\n";
        } else {
                std::cout << "Unknown command. Please try again.\n";
        }

        std::cout << "Enter command ('search_name', 'search_grade', 'sort', 'bonus', 'append', 'delete, 'above', 'exit'): ";
        std::getline(std::cin, command);
    }

    return 0;
}
