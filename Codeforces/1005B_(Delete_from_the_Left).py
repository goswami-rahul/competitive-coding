a = input()
b = input()
a = a[::-1]
b = b[::-1]
n = min(len(a), len(b))
ans = len(a) + len(b)
a = a[:n]
b = b[:n]
for x, y in zip(a, b):
    if x != y:
        break
    ans -= 2
print(ans)
