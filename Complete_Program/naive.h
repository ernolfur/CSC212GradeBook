#pragma once

#include <string>
#include <vector>

class Naive {
public:
    // Constructor
    Naive(const std::string& filename);
    
    // Member function to perform the naive pattern search
    void searchName(const std::string& pattern) const;
    void searchGrade(const std::string& pattern) const;
    void searchNamePart(const std::string& pattern) const;
    void deleteLine(const std::string& pattern, const std::string& filename);
    

private: 
    // Private member to hold lines read from file
    std::vector<std::string> lines;

    // Utility function to read lines from a CSV file
    void readCSV(const std::string &filename);
};