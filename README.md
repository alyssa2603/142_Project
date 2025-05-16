# Shortest Weight Constrained Path

The Shortest Weight Constrained Path is an NP-Hard problem that finds the shortest path between two specified nodes while ensuring the total weight of the path is less than or equal to a given weight constraint.

## Problem Definition
Given:
- A graph G = (V, E), where V is the set of vertices and E is the set of edges
- Each edge has a length value l and a weight value w
- Specified vertices s (source) and t (target)
- An integer W (weight constraint)

The goal is to find the shortest path from s to t such that the total weight of the path is ≤ W.

## Implemented Algorithms

### 1. Recursive DFS Backtracking Method (Brute Force)
- Explores every combination of vertices to find the shortest path under the weight constraint.
- Keeps track of the current least cost (length) while ensuring the weight remains under W.
- **Time Complexity**: O(|V|!), as it evaluates all possible vertex permutations.

### 2. Label Setting Algorithm (Dynamic Programming)
- Extends Dijkstra’s algorithm using a dynamic programming approach.
- Maintains labels for each node, where each label records the length and weight of a specific path.
- Bounds the maximum label count per vertex (e.g., max 100 labels) to achieve pseudo-polynomial time.
- **Time Complexity**: O(|V|²), due to the label count bound.
- **Pseudocode Reference**:  
  Dumitrescu, I., & Boland, N. (2001). Algorithms for the Weight Constrained Shortest Path Problem. *International Transactions in Operational Research, 8*(1), 15–29. https://doi.org/10.1111/1475-3995.00003

## Files
- `recursive_dfs.c`: Implements the Recursive DFS Backtracking Method (Brute Force).
- `dynamic_programming.c`: Implements the Label Setting Algorithm (Dynamic Programming).
- `test_50.in`: Test file with 50 vertices.
- `test_100.in`: Test file with 100 vertices.
- `test_150.in`: Test file with 150 vertices.
- `test_200.in`: Test file with 200 vertices.

**Note**: All provided test files contain graphs with a shortest path satisfying the sweight constraint.

## Testing
To compile and run the algorithms with a test file:
```bash
gcc recursive_dfs.c && ./a.out < test_50.in
```
Replace `recursive_dfs.c` with `dynamic_programming.c` to test the dynamic programming implementation, and `test_50.in` with the desired test file (e.g., `test_50.in`).
