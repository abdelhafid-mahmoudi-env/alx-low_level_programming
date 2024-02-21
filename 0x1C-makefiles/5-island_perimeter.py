#!/usr/bin/python3
"""
Function to calculate the perimeter of an island in a grid.
"""


def island_perimeter(grid):
    """
    Calculate the perimeter of the island described in grid.

    Args:
        grid (list of list of int): Grid representing the island.

    Returns:
        int: Perimeter of the island.
    """
    perimeter = 0
    rows = len(grid)
    cols = len(grid[0])

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 1:
                perimeter += 4  # Each land cell contributes 4 to the perimeter

                # Check neighbors to subtract overlapping sides
                if i > 0 and grid[i - 1][j] == 1:
                    perimeter -= 2  # Subtract 2 if the upper neighbor is also land
                if j > 0 and grid[i][j - 1] == 1:
                    perimeter -= 2  # Subtract 2 if the left neighbor is also land

    return perimeter
