n, d = map(int, input().split())
arr = list(map(int, input().split()))
if n == 1:
    ans = 2
else:
    s = set()
    s.add(arr[0] - d)
    s.add(arr[-1] + d)
    for i in range(n):
        if i == 0:
            if arr[i + 1] - arr[i] - d >= d:
                s.add(arr[i] + d)
        elif i == n - 1:
            if arr[i] - d - arr[i - 1] >= d:
                s.add(arr[i] - d)
        else:
            if arr[i + 1] - arr[i] - d >= d:
                s.add(arr[i] + d)
            if arr[i] - d - arr[i - 1] >= d:
                s.add(arr[i] - d)
    ans = len(s)
print(ans)
