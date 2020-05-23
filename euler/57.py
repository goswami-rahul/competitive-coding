n, d = 2, 1
ans = 0
for _ in range(1000):
    n, d = d, n
    n += d
    ans += len(str(n)) > len(str(d))
    n += d
print(ans)
