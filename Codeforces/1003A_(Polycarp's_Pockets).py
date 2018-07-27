n = int(input())
arr = list(map(int, input().split()))
ans = 1
for e in arr:
    ans = max(ans, arr.count(e))
print(ans)
