from string import ascii_uppercase as alpha
from math import gcd

def case():
    n, m = map(int, input().split())
    a = [int(x) for x in input().split()]
    p = -1
    for i in range(m - 1):
        if a[i] != a[i + 1]:
            p = i
            break
    ans = [None] * (m + 1)
    ans[p + 1] = gcd(a[p], a[p + 1])
    for i in range(p, -1, -1):
        ans[i] = a[i] // ans[i + 1]
    for i in range(p + 2, m + 1):
        ans[i] = a[i - 1] // ans[i - 1]
    primes = sorted(set(ans))
    d = {}
    for i in range(26):
        d[primes[i]] = alpha[i]
    s = ""
    for x in ans:
        s += d[x]
    return s
    
for i in range(int(input())):
    print("Case #{}: {}".format(i + 1, case()))