from sys import argv
from itertools import product, count, permutations
from copy import deepcopy
import re


def check_rule(rule, string):
    t, r = rule
    if t == "rule":
        return string == r
    elif t == "branch":
        for branch in r:
            if check_branch(branch, string):
                return True
        return False


def part1(f: list) -> int:
    unparsed = []
    strings = []
    for i, line in enumerate(f):
        if not line:
            unparsed = f[:i]
            strings = f[i + 1 :]
    rules = []
    for i, line in enumerate(unparsed):
        branch = re.findall(r"(\d[ \d]*)(?!:)", line)
        if branch:
            rules.append(
                tuple(tuple(map(int, b.strip().split(" "))) for b in branch)
            )
            continue
        rule = re.findall(r"\"[^\"]*\"", line)
        rules.append(rule[0][1:-1])

    print(rules)

    return check_rule(rules[0], strings[0])


def part2(f: list) -> int:
    return 0


def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(argv[1], "r")]

    print("Part 1:", part1(deepcopy(f)))
    print("Part 2:", part2(deepcopy(f)))


if __name__ == "__main__":
    main()
