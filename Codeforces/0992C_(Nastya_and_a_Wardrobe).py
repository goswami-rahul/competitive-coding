x, n = map(int, input().split())
MOD = 10**9 + 7
c = 4*x
if c == 0:
    ans = 0
elif n == 0:
    ans = 2 * x
else:
    ans = (((c - 2) * pow(2, n -1, MOD) + 1) + MOD) % MOD
print(ans % MOD)