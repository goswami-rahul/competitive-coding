n = int(input())
ans = "YES"
prev = float("inf")
for i in range(n):
    mn, mx = sorted(map(int, input().split()))
    if mx <= prev:
        prev = mx
    elif mn <= prev:
        prev = mn
    else:
        ans = "NO"
        break
print(ans)
