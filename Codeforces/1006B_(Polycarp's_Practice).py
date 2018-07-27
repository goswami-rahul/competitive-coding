# from collections import Counter as cc
n, k = map(int, input().split())
arr = list(map(int, input().split()))
s = sorted(zip(arr, range(n)), reverse=True)
s = s[:k]
print(sum(x for x, _ in s))
s.sort(key=lambda x: x[1])
prev = -1
ans = []
for x, i in s[:-1]:
    n -= i - prev
    ans.append(i - prev)
    prev = i
ans.append(n)
print(*ans)
