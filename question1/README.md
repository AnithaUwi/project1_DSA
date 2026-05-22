# Question 1 – Quick Sort

Reads student records from `students.txt`, sorts by **grade** (low to high).  
If two students have the same grade, sort by **last name** (lexicographic).

Writes result to `sorted_students.txt` (created when you run the program).

## Files

| File | Purpose |
|------|---------|
| `sort_students.c` | Main program |
| `students.txt` | Sample input |
| `analysis_q1.txt` | Time complexity + why quick sort over insertion sort |

## Run

```bash
gcc -o sort_students sort_students.c
./sort_students
```

Windows: `.\sort_students.exe`

Check `sorted_students.txt` after running.
