import sys
# sys.setrecursionlimit(2001)
def debug(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)
from math import gcd
INF = float("inf")
M = 10**9 + 7
def solve():
        n, m = map(int, input().split())
        fence  = []
        zom = []
        for _ in range(n - 1):
            fence.append(tuple(map(int, input().split())))
        for _ in range(m):
            y, h = map(int, input().split())
            zom.append((y - 1, h))
        # debug(fence)
        # debug(zom)
        # abletoreachD = [0] * n
        issafeN = [1] * n
        # issafeD = [1] * n
        for zy, zh in zom:
            debug("zy =", zy, ", zh =", zh)
            abletoreachN = [0] * n
            abletoreachN[zy] = 1
            # abletoreachD[zy] = 1
            for i in range(zy + 1, n):
                a, b = fence[i - 1]
                if a > zh:
                    p = 0
                elif b <= zh:
                    p = 1
                else:
                    num, den = zh - a + 1, b - a + 1
                    g = gcd(num, den)
                    num //= g
                    den //= g
                    p = (num * pow(den, M - 2, M)) % M
                    debug("num =", num, "den =", den)
                debug("i =", i, ", p =", p)
                abletoreachN[i] = (p * abletoreachN[i - 1]) % M
                # abletoreachD[i] = (den * abletoreachD[i - 1]) % M

            for i in range(zy - 1, -1, -1):
                a, b = fence[i]
                if a > zh:
                    p = 0
                elif b <= zh:
                    p = 1
                else:
                    num, den = zh - a + 1, b - a + 1
                    g = gcd(num, den)
                    num //= g
                    den //= g
                    p = (num * pow(den, M - 2, M)) % M
                    debug("num =", num, "den =", den)
                debug("i =", i, ", p =", p)
                abletoreachN[i] = (p * abletoreachN[i + 1]) % M
                # abletoreachD[i] = (den * abletoreachD[i + 1]) % M

            for i in range(n):
                # den = abletoreachD[i]
                # num = (M + den - abletoreachN[i]) % M
                p = (M + 1 - abletoreachN[i]) % M
                issafeN[i] = (p * issafeN[i]) % M
                # issafeD[i] = (den * issafeD[i]) % M
            debug("abletoreachN =", abletoreachN)
            debug("issafeN =", issafeN)

        unsafeN = [-1] * n
        # unsafeD = [-1] * n
        allunsafeN = 1
        # allunsafeD = 1
        for i in range(n):
            # den = issafeD[i]
            # num = (M + den - issafeN[i]) % M
            p = (M + 1 - issafeN[i]) % M
            unsafeN[i] = p
            # unsafeD[i] = den
            allunsafeN = (allunsafeN * p) % M
            # allunsafeD = (allunsafeD * den) % M

        # ansD = allunsafeD
        ansN = (M + 1 - allunsafeN) % M

        # ans = (ansN * pow(ansD, M - 2, M)) % M
        print(ansN)
        debug(ansN)

test = int(input())
# test = 3
for T in range(test):
    print(f"Case #{T+1}:", end=" ")
    solve()
    debug(f"Case #{T+1} solved!\n")
    # break
