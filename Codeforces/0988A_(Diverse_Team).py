n, k = map(int, input().split())
arr = list(map(int, input().split()))
s = set(arr)
if len(s) < k:
    print("NO")
else:
    print("YES")
    print(*[(arr.index(i) + 1) for i in s][:k])
