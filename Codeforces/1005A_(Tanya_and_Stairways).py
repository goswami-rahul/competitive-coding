n = int(input())
arr = list(map(int, input().split()))
arr = arr[1:]
arr.append(1)
prev = 1
ans = []
for e in arr:
    if e == 1:
        ans.append(prev)
    prev = e
print(len(ans))
print(*ans)
