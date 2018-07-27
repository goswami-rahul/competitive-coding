n, b = map(int, input().split())
arr = list(map(int, input().split()))
odd = 0
even = 0
cut = []
for i in range(n-1):
    if arr[i] % 2 == 0:
        even += 1
    else:
        odd += 1
    if odd == even:
        cut.append(abs(arr[i+1] - arr[i]))
# print(cut)
cut.sort()
# print(cut)
ans = 0
while b > 0 and cut:
    if b - cut[0] < 0:
        break
    b -= cut[0]
    cut.pop(0)
    ans += 1
    # print(ans, cut)
print(ans)
