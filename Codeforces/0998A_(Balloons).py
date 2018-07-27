n = int(input())
arr = list(map(int, input().split()))
if n == 1:
    k = -1
elif n == 2 and arr[0] == arr[1]:
    k = -1
else:
    k = 1
    ans = [1]
    if arr[0] == sum(arr[1:]):
        ans.append(2)
        k = 2
print(k)
if k != -1:
    print(*ans)
