from sys import stdout
def solve():
    m, n = list(map(int, input().split()))
    seq = [-1] * n
    lo = 1
    hi = m
    for i in range(n):
        print(1)
        stdout.flush()
        t = int(input())
        if t == 0:
            return
        if t == 1:
            seq[i] = 1
        else:
            seq[i] = 0
    i = 0
    while True:
        mid = (hi + lo) // 2
        print(mid)
        stdout.flush()
        t = int(input())
        if t == 0:
            return
        if not seq[i]:
            if t== 1: t = -1
            else: t = 1
        if t == 1:
            lo = mid + 1
        else:
            hi = mid - 1
        i = (i + 1) % n

solve()
