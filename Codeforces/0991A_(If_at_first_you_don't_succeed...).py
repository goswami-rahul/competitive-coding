a, b, c, n = map(int, input().split())
n -= 1
if n == -1:
    ans = -1
elif c > a or c > b or a > n or b > n or c > a + b or c > n or c < a + b - n:
    ans = -1
else:
    ans = n - (a + b - c) + 1
    if ans < 1:
        ans = -1
print(ans)