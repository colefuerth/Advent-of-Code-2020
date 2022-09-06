from sys import argv
from itertools import product, count, permutations
from copy import deepcopy
import re


def check_rule(rule: int, rules: list, string: str):
    if string == '':
        raise ValueError('String is empty')
    rule = rules[rule]
    if type(rule) == str:
        return string[1:] if string.startswith(rule) else string
    for branch in rule:
        s = string
        for leaf in branch:
            st = check_rule(leaf, rules, s)
            if st == s:
                break
            s = st
        if s == '':
            return s
    return string


def part1(f: list) -> int:
    unparsed = []
    strings = []
    for i, line in enumerate(f):
        if not line:
            unparsed = f[:i]
            strings = f[i + 1:]
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

    results = []
    for s in strings:
        r = check_rule(0, rules, s)
        print(s, r)
        results.append(r == '')
    return sum(results)


def part2(f: list) -> int:
    return 0


def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(argv[1], "r")]

    print("Part 1:", part1(deepcopy(f)))
    print("Part 2:", part2(deepcopy(f)))


if __name__ == "__main__":
    main()
