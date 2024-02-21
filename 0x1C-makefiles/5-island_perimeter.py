#!/usr/bin/python3
"""Function to calculate the perimeter of an island in a grid."""


def island_perimeter(grid):
    """Calculate the perimeter of the island described in grid."""
    c = 0
    rows = len(grid) - 1
    cols = len(grid[0]) - 1

    for i, r in enumerate(grid):
        for j, n in enumerate(r):
            if n == 1:
                if i == 0 or grid[i - 1][j] != 1:
                    c += 1
                if j == 0 or grid[i][j - 1] != 1:
                    c += 1
                if j == cols or grid[i][j + 1] != 1:
                    c += 1
                if i == rows or grid[i + 1][j] != 1:
                    c += 1
    return c
