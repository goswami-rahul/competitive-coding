dsum = lambda x: sum(int(c) for c in str(x))
ans = 1
for a in range(1, 100):
    val = 1
    for b in range(1, 100):
        val *= a
        ans = max(ans, dsum(val))
print(ans)
