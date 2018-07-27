n = int(input())
arr = []
for _ in range(n):
    s = input()
    arr.append(s)
arr.sort(key=len)
prev = ''
for s in arr:
    if prev not in s:
        print("NO")
        break
    prev = s
else:
    print("YES")
    print("\n".join(arr))
