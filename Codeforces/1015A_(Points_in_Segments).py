n, m = map(int, input().split())
s = set(range(1, m + 1))
for _ in range(n):
    l, r = map(int, input().split())
    for i in range(l, r + 1):
        s.discard(i)
print(len(s))
print(*s)
