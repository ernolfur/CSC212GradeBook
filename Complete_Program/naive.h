#ifndef NAIVE_H
#define NAIVE_H

#include <string>
#include <vector>

class Naive {
public:
    // Constructor
    Naive(const std::string& filename);
    
    // Member functions to perform the naive pattern search
    void searchName(const std::string& pattern) const;
    void searchGrade(const std::string& pattern) const;

private:
    // Private member to hold lines read from file
    std::vector<std::string> lines;

    // Utility function to read lines from a CSV file
    void readCSV(const std::string &filename);
};

#endif
