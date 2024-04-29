# Gradebook Management Microcosm Documentation
This file contains all of our documentation relating to the Gradebook program. Contains everything you need to know including usage, installation instructions, and functionality.
# Research Project Structure 
- Data Structures: B-Tree, Skip List
- Algorithm: Naive Algorithm
## Microcosm
We are going to be creating a **gradebook management program**. 

Users will be able to store and manage data relating to information stored in a real gradebook.

This program will be designed to simulate fundamental features of a typical gradebook system such as in CSC212.

We hope to show in our program that we gained a more in-depth understanding of data structure implementation and system design.
## Data
- First and Last Name
- Lab and Assignment Grades (out of 100)
- Attendance
  
Example Format:
```
Name,LabGrade1,LabGrade2,AssignmentGrade1,AssignmentGrade2,Attendance
"John Doe",89,93,80,75,"Yes"
"Jane Doe",45,99,100,67,"No"
"Alice Johnson",82,88,91,78,"Yes"
"Bob Brown",90,85,87,93,"Yes"
"Charlie Smith",77,84,75,85,"No"
"Diana Prince",68,75,70,80,"Yes"
"Evan Wright",88,90,85,84,"No"
"Fiona Glenanne",92,87,90,88,"Yes"
"Gregory House",73,80,77,69,"No"
"Hannah Abbott",85,80,82,86,"Yes"
"Ivan Rogers",78,74,88,90,"No"
"Jessica Day",95,92,89,91,"Yes"

```

## General Features
- Sort grades highest to lowest
- Flexible Grading Scale: Calculates average
- Search student info by name and grade.
- insertion, deletion, sorting of student info
- handle multiple search queries

# Tasks For Each D&A
This program will hold all student data in series of nested data structures. Each data structure/algorithm we code will be programmed to be able to hold a variety of data types, namely using C++ templates. This way we can use the same data structure to hold name strings, grade floats, and even other data structures.

## Naive Algorithm (Kai)
- Search student information by name, output whole line if found.
- Search student information by grade, output whole line if found.
- Delete line given a students name
- Description: 
A naive algorithm solves problems using the most straightforward and obvious approach, often involving a brute-force search through all possible solutions to find the correct one.
## B-tree (Adam)
- Append insert new entire student information into input .csv file
- Sort grades from highest to lowest by average and output
- output students who receive bonus for reaching attendance count threshold
- Description: 
A B-tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. It is commonly used in databases and file systems to allow quick data retrieval and manipulation even with large volumes of data.
## Skip-List (Skye)
- Delete entire line student information by searching name
- given a grade range, output grade counts that are within this range. (ex: amount of grades within 80-90)
- output students that are passing/failing based on grade average. (ex: avg_grade >= 65 = passing. avg_grade < 65 failing.)
- Description: A Skip List is a probabilistic data structure that enhances the efficiency of searching within an ordered sequence of elements, similar to a sorted linked list but with additional layers that enable fast access paths across the list.

## Main (Anish)
- handle data from .csv file (strings/int)
- properly store data
- output correctly
- read in data from .csv file
- write out data to .csv file
