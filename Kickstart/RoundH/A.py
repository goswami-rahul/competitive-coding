def test_case():
    n, p = map(int, input().split())
    a = set()
    for _ in range(p):
        a.add(input())
    a = list(a)
    seen = set()
    p = len(a)
    for i in range(p):
        for j in range(p):
            if i == j:
                continue
            if len(a[i]) < len(a[j]):
                if a[i] == a[j][:len(a[i])]:
                    seen.add(j)
    ans = 2 ** n
    for i in range(p):
        if i not in seen:
            ans -= (2 ** (n - len(a[i])))
    print(ans)

import sys
for t in range(1, int(input()) + 1):
    print(f"Case #{t}: ", end="")
    test_case()
    sys.stderr.write(f"Case {t} solved!\n")
