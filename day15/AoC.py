from sys import argv

def simulate(f:list, turns) -> int:
    history = {k:i+1 for i, k in enumerate(f[:-1])}
    nextspoken = f[-1]
    for turn in range(len(f), turns):
        if nextspoken not in history:
            history[nextspoken] = turn
            nextspoken = 0
        else:
            prev = nextspoken
            nextspoken = turn - history[nextspoken]
            history[prev] = turn
    return nextspoken

def main():
    # start by getting file as a list of strings
    f = [l.strip() for l in open(argv[1], 'r')]
    inp = [int(i) for i in f[0].split(',')]

    print("Part 1:", simulate(inp, 2020))
    print("Part 2:", simulate(inp, 30000000))


if __name__ == "__main__":
    main()