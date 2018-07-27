n, k = map(int, input().split())
arr = list(map(int, input().split()))
c = 0
while True:
    if len(arr) == 0:
        break
    if arr[0] > k:
        break
    arr.pop(0)
    c += 1
while True:
    if not arr:
        break
    if arr[-1] > k:
        break
    arr.pop()
    c += 1
print(c)
