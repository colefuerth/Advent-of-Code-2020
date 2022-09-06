from sys import argv, setrecursionlimit
from itertools import product, count, permutations
from copy import deepcopy
import re


def check_rule(rule: int, rules: list, string: str, level: int = -1, history: set = set()) -> str:
    history = history.copy()
    if rule in history:
        return string
    history.add(rule)
    level += 1
    padding = "| " * level
    if string == '':
        raise ValueError('String is empty')
    # print(f'{padding}checking rule {rule}: {rules[rule]} with string {string}')
    rule = rules[rule]
    if type(rule) == str:
        return string[1:] if string.startswith(rule) else string
    possibliities = []
    for branch in rule:
        # print(f'{padding}checking branch {branch} against {string}')
        s = string
        nochange = False
        for leaf in branch:
            st = check_rule(leaf, rules, s, level, history)
            if st == s:
                nochange = True
                break
            s = st
        if not nochange:
            possibliities.append(s)
    return string if not possibliities else min(possibliities, key=len)


def part1(f: list) -> int:
    strings = f[f.index('') + 1:]
    rules = {}
    for line in f[:f.index('')]:
        i = int(line.split(':')[0])
        rule = re.findall(r"\"[^\"]*\"", line)
        if rule:
            rules[i] = rule[0][1:-1]
            continue
        branch = re.findall(r"(\d[ \d]*)(?!.*:)", line)
        rules[i] = tuple(tuple(map(int, b.strip().split(" "))) for b in branch)

    results = []
    for s in strings:
        r = check_rule(0, rules, s)
        results.append(r == '')
    return sum(results)


def check_rule2(rule: int, rules: list, string: str, level: int = -1, maxdepth:int=None) -> str:
    if maxdepth is None:
        maxdepth = len(string)
    level += 1
    if level > maxdepth or string == '':
        return string
    padding = "| " * level
    print(f'{padding}checking rule {rule}: {rules[rule]} with string {string}')
    rule = rules[rule]
    if type(rule) == str:
        return string[1:] if string.startswith(rule) else string
    possibliities = []
    for branch in rule:
        print(f'{padding}checking branch {branch} against {string}')
        s = string
        nochange = False
        for leaf in branch:
            st = check_rule2(leaf, rules, s, level, maxdepth)
            if st == s:
                nochange = True
                break
            s = st
        if not nochange:
            possibliities.append(s)
    return string if not possibliities else min(possibliities, key=len)


def part2(f: list) -> int:
    strings = f[f.index('') + 1:]
    rules = {}
    for line in f[:f.index('')]:
        i = int(line.split(':')[0])
        rule = re.findall(r"\"[^\"]*\"", line)
        if rule:
            rules[i] = rule[0][1:-1]
            continue
        branch = re.findall(r"(\d[ \d]*)(?!.*:)", line)
        rules[i] = tuple(tuple(map(int, b.strip().split(" "))) for b in branch)

    # replace rules 8 and 11
    changes = ['8: 42 | 42 8',
               '11: 42 31 | 42 11 31']
    for line in changes:
        i = int(line.split(':')[0])
        branch = re.findall(r"(\d[ \d]*)(?!.*:)", line)
        rules[i] = tuple(tuple(map(int, b.strip().split(" "))) for b in branch)

    results = []
    for s in strings:
        r = check_rule2(0, rules, s)
        results.append(r == '')
    return sum(results)


def main():
    inpfile = argv[1] if len(argv) > 1 else "input.txt"
    f = [l.strip() for l in open(inpfile, "r")]

    print("Part 1:", part1(deepcopy(f)))
    print("Part 2:", part2(deepcopy(f)))


if __name__ == "__main__":
    main()
