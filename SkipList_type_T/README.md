# Notes

- Node are automatically sorted
  - Thus the data must be something that can compared (eg. int, float, string)
- search() returns a pointer to a node, so by adding another data type to the node, the list can function like a map

# Files

main.cpp: file input handling & command calls

test.txt: sample test input for main.cpp

skip_list.h: class implementation

node.h: class implementation for node class used in skip_list

# Commands

input() - puts passed data into the list as a new node, sorted into the right position

search() - searches for a node with passed data in the list, returns pointer to it (nullptr if nonexistent)

remove() - removes first instance of a node containing passed data from the list

## Compile Commands

```
g++ main.cpp -o prog -std=c++11

./prog

```
