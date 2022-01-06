import sys
from itertools import product
# from collections import defaultdict
# from copy import deepcopy


def adjacent(coord):
    # grid is a defaultdict that yields '.' default, or '#' if coord is active
    x, y, z = coord
    adj = [(x + dx, y + dy, z + dz)
           for dx, dy, dz in product([-1, 0, 1], repeat=3)]
    adj.remove(coord)
    return adj

def expand(grid):
    # expand the grid to include all coords around any active cubes
    for cube, state in grid.copy().items():
        if state:
            for c in adjacent(cube):
                if c not in grid:
                    grid[c] = 0


def activeadj(grid, coord):
    return sum(grid[c] for c in adjacent(coord) if c in grid)


def parsecube(f: list):
    # parse the input into a 3D grid of '.' and '#'
    grid = {}
    for y, line in enumerate(f):
        for x, c in enumerate(line):
            grid[x, y, 0] = 1 if c == '#' else 0
    return grid


def part1(f: list, cycles: int) -> int:
    # start by parsing the initial state
    grid = parsecube(f)
    for _ in range(cycles):
        expand(grid)
        # print(sum(grid.values()))
        # print(f'active: {[c for c, s in grid.items() if s == 1]}')
        gridimage = grid.copy()
        for cube, state in gridimage.items():
            if state:
                if activeadj(gridimage, cube) not in (2, 3):
                    grid[cube] = 0
            else:
                if activeadj(gridimage, cube) == 3:
                    grid[cube] = 1
    return sum(grid.values())


def adjacent4d(coord):
    # grid is a defaultdict that yields '.' default, or '#' if coord is active
    x, y, z, w = coord
    adj = [(x + dx, y + dy, z + dz, w + dw)
           for dx, dy, dz, dw in product([-1, 0, 1], repeat=4)]
    adj.remove(coord)
    return adj

def expand4d(grid):
    # expand the grid to include all coords around any active cubes
    for cube, state in grid.copy().items():
        if state:
            for c in adjacent4d(cube):
                if c not in grid:
                    grid[c] = 0


def activeadj4d(grid, coord):
    return sum(grid[c] for c in adjacent4d(coord) if c in grid)


def parsecube4d(f: list):
    # parse the input into a 3D grid of '.' and '#'
    grid = {}
    for y, line in enumerate(f):
        for x, c in enumerate(line):
            grid[x, y, 0, 0] = 1 if c == '#' else 0
    return grid


def part2(f: list, cycles: int) -> int:
    # start by parsing the initial state
    grid = parsecube4d(f)
    for _ in range(cycles):
        expand4d(grid)
        # print(sum(grid.values()))
        # print(f'active: {[c for c, s in grid.items() if s == 1]}')
        gridimage = grid.copy()
        for cube, state in gridimage.items():
            if state:
                if activeadj4d(gridimage, cube) not in (2, 3):
                    grid[cube] = 0
            else:
                if activeadj4d(gridimage, cube) == 3:
                    grid[cube] = 1
    return sum(grid.values())


def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(sys.argv[1], 'r')]

    print("Part 1:", part1(f, 6))
    print("Part 2:", part2(f, 6))


if __name__ == "__main__":
    main()
