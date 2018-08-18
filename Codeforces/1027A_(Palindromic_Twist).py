def solve():
    n = int(input())
    s = input()
    e = ord('a')
    a, b = s[: n // 2], s[n // 2:]
    b = b[::-1]
    for x, y in zip(a, b):
        i = ord(x) - e
        j = ord(y) - e
        if abs(i - j) == 0 or abs(i - j) == 2:
            continue
        print("NO")
        return
    print("YES")

for _ in range(int(input())):
    solve()
