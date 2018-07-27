
n, m, a, b = map(int, input().split())
ans = min(b * (n % m), a * (m - (n % m)))
print(ans)
