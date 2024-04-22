# Files
skip_list.h: function definition
skip_list.cpp: function implementation
main.cpp: file input handling & command calls
test.txt: sample test input for main.cpp

# Commands
- input(): puts passed data into the list as a new node, sorted into the right position

- search(): searches for a node with passed data in the list, returns pointer to it (nullptr if nonexistent)

- remove(): removes first instance of a node containing passed data from the list

## Compile Commands

```
g++ main.cpp skip_list.cpp node.cpp -o prog -std=c++11

./prog

```
