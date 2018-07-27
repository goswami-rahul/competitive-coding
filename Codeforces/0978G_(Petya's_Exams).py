n, m = map(int, input().split())
arr = []
for i in range(1, m + 1):
    s, d, c = map(int, input().split())
    arr.append((d, s, c, i))
arr.sort()
ans = [0] * (n + 1) 
for d, s, c, i in arr:
    j = s
    ef = False
    for k in range(c):
        while j < d and ans[j] != 0:
            j += 1
        if j >= d:
            ef = True
            break
        ans[j] = i
    if ef:
        print(-1)
        break
    if ans[d] == 0:
        ans[d] = m + 1
    else:
        print(-1)
        break
else:
    print(*ans[1:])
