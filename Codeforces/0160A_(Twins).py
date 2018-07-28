n = int(input())
arr = sorted(map(int, input().split()), reverse=True)
k = sum(arr)
s = k // 2
cur = 0
i = 0
for e in arr:
    cur += e
    i += 1
    if cur > s:
        print(i)
        break
