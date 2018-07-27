n = int(input())
orig = sorted(map(int, input().split()))
# orig = arr[:]
cur = 0
ans = 0
p = 0
while p + 1 < n:
    p = p + 1
    if orig[p] > orig[cur]:
        ans += 1
        cur += 1
print(ans)
