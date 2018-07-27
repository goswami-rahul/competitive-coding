from collections import defaultdict as dd
d = dd(int)

n = int(input())
for _ in range(n):
    a, x = map(int, input().split())
    d[a] = x
m = int(input())
for _ in range(m):
    b, y = map(int, input().split())
    if y > d[b]:
        d[b] = y
print(sum(d.values()))
