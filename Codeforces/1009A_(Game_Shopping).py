n, m = map(int, input().split())
cost = list(map(int, input().split()))
bill = list(map(int, input().split()))
ans = 0
bill.reverse()
for c in cost:
    if bill:
        if bill[-1] >= c:
            bill.pop()
            ans += 1
    # print(c, ans)
print(ans)
