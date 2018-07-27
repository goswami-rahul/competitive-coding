n = int(input())
arr = list(map(int, input().split()))
mn = min(arr)
# arr = [i - mn for i in arr]
pos = mn % n
val = mn
for _ in range(n):
    if arr[pos] <= val:
        ans = pos
        break
    pos = (pos + 1) % n
    val += 1
print(ans + 1)
