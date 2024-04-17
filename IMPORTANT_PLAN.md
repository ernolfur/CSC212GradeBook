# Research Project Structure                      (plan in progress)
- Data Structures: B-Tree, Skip List
- Algorithm: Naive Algorithm
## Objective
We are going to be creating a **gradebook management program**. 

Users will be able to store and manage data relating to information stored in a real gradebook.

This program will be designed to simulate fundamental features of a gradebook system. 

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

## Features
- Sort grades highest to lowest
- Flexible Grading Scale: Calculate mean, median, mode
- Search student info(names,grades,etc)
- insertion, deletion, sorting of student info
- handle grade range queries

# Tasks For Each D&A
This program will hold all student data in series of nested data structures. Each data structure/algorithm we code will be programmed to be able to hold a variety of data types, namely using C++ templates. This way we can use the same data structure to hold name strings, grade floats, and even other data structures.

## Naive Algorithm (Kai)
- Calculate grade mean, median, and mode for whole class.
- Search student information by name, output whole line if found.
- Search student information by grade, output whole line if found.

## B-tree (Adam)
- Append insert new entire student information into input .csv file
- Sort grades from highest to lowest by average and output
- output students who receive bonus for reaching attendance count threshold
  
## Skip-List (Skye)
- Delete entire line student information by searching name
- given a grade range, output grade counts that are within this range. (ex: amount of grades within 80-90)
- output students that are passing/failing based on grade average. (ex: avg_grade >= 65 = passing. avg_grade < 65 failing.)

## Main (Anish)
- handle data from .csv file (strings/int)
- properly store data
- output correctly
- read in data from .csv file
- write out data to .csv file


in progress..


 


