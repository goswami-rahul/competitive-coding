from collections import Counter as cc
n, k = map(int, input().split())
s = input()
c = cc(s)
alpha = 'abcdefghijklmnopqrstuvwxyz'
for a in alpha:
    if k > c[a]:
        k -= c[a]
        c[a] = 0
    else:
        c[a] -= k
        k = 0
    if k == 0:
        break
lst = []
for a in s[::-1]:
    if c[a] > 0:
        c[a] -= 1
        lst.append(a)
print("".join(lst[::-1]))
