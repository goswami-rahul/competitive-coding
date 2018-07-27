n = int(input())
arr = sorted(map(int, input().split()))
m1 = 0
i = 2
m2 = 0
j = n - 1
for e in arr:
    m1 += abs(e - i)
    i += 2
for e in arr[::-1]:
    m2 += abs(e - j)
    j -= 2
print(min(m1, m2))
