# Week 3 Formative 1 — Data Structures (C)

**Repository:** [https://github.com/AnithaUwi/project1_DSA](https://github.com/AnithaUwi/project1_DSA)

C programs for the Week 3 formative assignment . Each question has its own folder with source code, input files where needed, written analysis, and a short README.



## Contents

| Folder | Topic | Main file |
|--------|--------|-----------|
| [question1](question1/) | Quick sort — student grades from file | `sort_students.c` |
| [question2](question2/) | Doubly linked list — bus route navigation | `bus_route.c` |
| [question3](question3/) | Binary tree — 68 component IDs | `binary_tree.c` |
| [question4](question4/) | BST — search students by last name | `bst_students.c` |

Algorithm write-ups: `analysis_q1.txt` … `analysis_q4.txt` inside each folder.

---

## How to compile and run

Needs **GCC** (MinGW on Windows, or `gcc` on Mac/Linux).

Open a terminal **inside** the question folder you want to run:

**Question 1**
```bash
gcc -o sort_students sort_students.c
./sort_students          # Windows: sort_students.exe
```
Reads `students.txt`, writes `sorted_students.txt`.

**Question 2**
```bash
gcc -o bus_route bus_route.c
./bus_route
```
Enter stops at the start, then use the menu. Forward/backward waits **3 seconds** between stops (required by the assignment).

**Question 3**
```bash
gcc -o binary_tree binary_tree.c
./binary_tree
```
Shows root and leaves, then enter a node value to query (0 to quit).

**Question 4**
```bash
gcc -o bst_students bst_students.c
./bst_students
```
Loads `students.txt`, search by last name from the menu.

---

## Question summary

**Q1** — Quick sort by grade (ascending). Same grade → sort by last name.  
**Q2** — Doubly linked list; forward (home→campus), backward, add stop at end.  
**Q3** — BST insertion; print root, leaves, parent, siblings, grandchildren.  
**Q4** — BST keyed by last name; duplicates go right; search lists all matches.

---

## What is not in this repo

- Compiled `.exe` / `.out` files (see `.gitignore`)
- `question1/sorted_students.txt` is generated when you run Q1

---

## Submission

The LMS document points to this GitHub repo. All required code and analysis are under `question1`–`question4`.

Tested with GCC on Windows.
