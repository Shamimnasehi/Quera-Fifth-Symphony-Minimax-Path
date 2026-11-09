# Fifth Symphony (Minimax Path in a Grid)

Algorithm Design - Homework 1, Problem 1 (Heap & Greedy algorithms)

- **Time limit:** 1 second
- **Memory limit:** 256 MB

## Problem

An `n x m` grid is given, where each cell holds a "sound level" `H[i][j]`.
Starting at the top-left cell `(0, 0)`, you must reach the bottom-right cell
`(n-1, m-1)`, moving only up, down, left, or right (no diagonal moves).

- The *sound difference* between two adjacent cells is `|H[a] - H[b]|`.
- The *sound jump* of a path is the largest sound difference between any two
  consecutive cells on that path.

Find a path whose sound jump is as small as possible, and print that value.

### Input

- First line: two integers `n` and `m` (rows and columns).
- Next `n` lines: `m` integers each, the sound levels of that row.

Constraints:

```
1 <= n, m <= 10^3
0 <= H[i][j] <= 10^9
```

### Output

A single integer: the minimum possible sound jump.

### Example

Input:

```
3 3
1 2 2
3 8 2
5 3 5
```

Output:

```
2
```

The path `1 -> 3 -> 5 -> 3 -> 5` has consecutive differences `2, 2, 2, 2`,
so its sound jump is `2`.

## Solution

This is a *minimax path* problem, solved with a modified Dijkstra.

- Let `dist[v]` be the smallest possible maximum jump over all paths from
  `(0, 0)` to cell `v`.
- Instead of summing edge weights, a path's cost is the **maximum** edge on it:
  `dist[v] = min(dist[v], max(dist[u], |H[u] - H[v]|))`.
- Extending a path can never lower its cost, so Dijkstra's greedy argument
  (always finalize the cell with the smallest `dist`) remains correct.
- A min-heap picks the next cell. Stale heap entries are skipped, and the loop
  stops as soon as the target cell is popped.

**Complexity:** `O(n*m*log(n*m))` time and `O(n*m)` memory.

### Alternative

Binary search on the answer `x`, and for each `x` run a BFS/DFS that only uses
moves with difference `<= x`. This is `O(n*m*log(max H))`, also valid.

## Build & Run

```bash
g++ -std=c++17 -O2 Q1.cpp -o Q1
./Q1 < input.txt
```

> Note: `-std=c++17` is required because the code uses structured bindings.
