input()
s = set(map(int, input().split()))
ans = len(s)
if 0 in s:
    ans -= 1
print(ans)
