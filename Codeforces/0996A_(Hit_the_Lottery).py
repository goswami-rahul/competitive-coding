n = int(input())
ans = 0
if n >= 100:
    ans += (n // 100)
    n %= 100
if n >= 20:
    ans += (n // 20)
    n %= 20
if n >= 10:
    ans += (n // 10)
    n %= 10
if n >= 5:
    ans += (n // 5)
    n %= 5
if n >= 1:
    ans += n
print(ans)
