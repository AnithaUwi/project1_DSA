# Question 4 – BST student records

Loads students from `students.txt` (format: `First|Last|Grade`).

Builds a **BST ordered by last name**.  
If two students share a last name, the duplicate goes to the **right** subtree.  
Search prints **all** records with that last name.

## Files

| File | Purpose |
|------|---------|
| `bst_students.c` | Main program |
| `students.txt` | Sample input (includes two "Smith" entries) |
| `analysis_q4.txt` | Search complexity, BST vs binary tree, BST vs file search |

## Run

```bash
gcc -o bst_students bst_students.c
./bst_students
```

Menu: **1** = search by last name, **2** = quit.  
Try searching `Smith` to see both records.
