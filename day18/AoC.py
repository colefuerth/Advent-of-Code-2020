import sys
from itertools import product, count, permutations
from copy import deepcopy
import re

# AoC template for python3

# do recursive parsing calls


def parse(s: str) -> int:
    p = re.findall(r'\([^()]*\)', s)
    while p:
        s = s.replace(p[0], str(parse(p[0][1:-1])), 1)
        p = re.findall(r'\([^()]*\)', s)

    o = re.findall(r'\d+ [\+\*] \d+', s)
    while o:
        s = s.replace(o[0], str(eval(o[0])), 1)
        o = re.findall(r'\d+ [\+\*] \d+', s)
    return int(s)


def part1(f: list) -> int:
    return sum(parse(l) for l in f)


def parse2(s: str) -> int:
    p = re.findall(r'\([^()]*\)', s)
    while p:
        s = s.replace(p[0], str(parse2(p[0][1:-1])), 1)
        p = re.findall(r'\([^()]*\)', s)

    for rs in [r'\d+ [\+] \d+', r'\d+ [\*] \d+']:
        o = re.findall(rs, s)
        while o:
            s = s.replace(o[0], str(eval(o[0])), 1)
            o = re.findall(rs, s)
    return int(s)


def part2(f: list) -> int:
    res = [parse2(l) for l in f]
    return sum(parse2(l) for l in f)


def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(sys.argv[1], 'r')]

    print("Part 1:", part1(deepcopy(f)))
    print("Part 2:", part2(deepcopy(f)))


if __name__ == "__main__":
    main()
