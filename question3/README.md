# Question 3 – Binary tree

Builds a tree from **68 distinct integers** in the source file.

**Insertion rule:** Binary Search Tree — smaller values go **left**, larger go **right**.

The program prints the root and all leaf nodes, then lets you type a value to see:

- parent  
- siblings  
- grandchildren  

Enter **0** to quit. Invalid values print an error and don’t crash.

## Files

| File | Purpose |
|------|---------|
| `binary_tree.c` | Main program (array + tree logic) |
| `analysis_q3.txt` | Insert time complexity |

## Run

```bash
gcc -o binary_tree binary_tree.c
./binary_tree
```

Try node `25` for a sample query, or `999` to test invalid input.
