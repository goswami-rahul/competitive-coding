p1, p2, t1, t2 = map(int, input().split())
x1 = max(3 * p1 / 10, p1 - p1 * t1 / 250)
x2 = max(3 * p2 / 10, p2 - p2 * t2 / 250)
if x1 == x2:
    ans = "Tie"
elif x1 > x2:
    ans = "Misha"
else:
    ans = "Vasya"
print(ans)
