from sys import argv
from itertools import product, count, permutations
from copy import deepcopy
import re

# AoC template for python3

def part1(f:list) -> int:
    return 0

def part2(f:list) -> int:
    return 0

def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(argv[1], 'r')]

    print("Part 1:", part1(deepcopy(f)))
    print("Part 2:", part2(deepcopy(f)))


if __name__ == "__main__":
    main()