//https://www.educative.io/answers/the-naive-algorithm-for-pattern-searching 
#include "naive.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>  // For std::tolower
#include <cmath>   // For std::fabs
#include <iomanip> // For std::setprecision
#include <vector>

Naive::Naive(const std::string& filename) {
    readCSV(filename);
}

void Naive::readCSV(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
}

void Naive::searchName(const std::string& pattern) const {
    std::string mod_pattern = pattern;  // Using the pattern directly
    bool found = false;

    std::cout << "Searching for names starting with: " << pattern << std::endl;

    for (const auto& line : lines) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string name = line.substr(1, commaPos - 1);  // Adjust to correctly extract the name
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            std::transform(mod_pattern.begin(), mod_pattern.end(), mod_pattern.begin(), ::tolower);
            if (name.find(mod_pattern) == 0) {  // Match must start at the beginning
                std::cout << "Name found: " << line << std::endl;
                found = true;
            }
        }
    }

    if (!found)
        std::cout << "Name not found." << std::endl;
}

void Naive::searchGrade(const std::string& pattern) const {
    double averageGrade = 0;
    try {
        averageGrade = std::stod(pattern);  // Attempt to convert string to double
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid grade input. Please ensure you enter a numeric value." << std::endl;
        return;  // Exit the function if conversion fails
    }

    std::cout << "Searching for students with this grade: " << std::fixed << std::setprecision(2) << averageGrade << std::endl;
    bool found = false;

    for (const auto& line : lines) {
        std::stringstream ss(line);
        std::string segment;
        double grade;
        while (getline(ss, segment, ',')) {
            std::stringstream gradeStream(segment);
            if (gradeStream >> grade) {
                if (std::fabs(grade - averageGrade) < 0.001) {  // Checking if the grades are essentially equal
                    std::cout << "Matching grade found in: " << line << std::endl;
                    found = true;
                }
            }
        }
    }

    if (!found)
        std::cout << "No matching grades found." << std::endl;
}

void Naive::deleteLine(const std::string& pattern, const std::string& filename) {
    std::string mod_pattern = pattern;
    std::transform(mod_pattern.begin(), mod_pattern.end(), mod_pattern.begin(), ::tolower);  // Convert pattern to lowercase for case-insensitive comparison
    bool found = false;

    auto it = std::remove_if(lines.begin(), lines.end(), [&](const std::string& line) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string name = line.substr(0, commaPos);  // Extract the name
            if (!name.empty() && name.front() == '"') {   // Check if the name is enclosed in quotes
                name = name.substr(1, name.length() - 2); // Remove the enclosing quotes
            }
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);  // Convert to lowercase
            if (name == mod_pattern) {
                found = true;
                return true;  // Return true if the name exactly matches the pattern to delete it
            }
        }
        return false;  // Keep the line if no comma is found or the name does not match exactly
    });

    if (found) {
        std::cout << "Deleting lines matching pattern: " << pattern << std::endl;
        lines.erase(it, lines.end());  // Remove the lines that match the pattern

        // Write the updated data back to the file
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Failed to open the file for writing: " << filename << std::endl;
            return;
        }
        for (const auto& line : lines) {
            outFile << line << std::endl;
        }
        outFile.close();
        std::cout << "File updated successfully.\n";
    } else {
        std::cout << "No matching names found for deletion.\n";
    }
}