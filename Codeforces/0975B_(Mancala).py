arr = list(map(int, input().split()))
ans = 0
for i in range(14):
    r = arr[i]//14
    d = arr[i] % 14
    c = 0
    x = (i + 1) % 14
    s = 0
    temp2 = arr[i]
    arr[i] = 0
    while c < 14:
        c += 1
        temp = arr[x] + r
        if d > 0:
            temp += 1
        d -= 1
        x = (x + 1) % 14
        s += (0 if temp % 2 else temp)
    arr[i] = temp2
    ans = max(ans, s)
print(ans)
