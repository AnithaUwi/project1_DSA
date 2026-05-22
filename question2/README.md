# Question 2 – Bus route (doubly linked list)

Models a bus line with a **doubly linked list**. You enter stops at the start, then use a menu to:

1. Go **forward** (home → campus) — 3 second pause between stops  
2. Go **backward** (campus → home) — same delay  
3. **Add** a new stop at the end  
4. **Exit** — frees all memory  

## Files

| File | Purpose |
|------|---------|
| `bus_route.c` | Main program |
| `analysis_q2.txt` | Time complexity for insert at end |

## Run

```bash
gcc -o bus_route bus_route.c
./bus_route
```

Enter how many stops you want, then names/numbers when prompted.  
Forward/backward takes a few seconds per gap — that’s intentional.
