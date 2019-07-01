MOD = 10**9 + 7
def solve():
    n = int(input())
    up = input()
    mid = input()
    down = input()
    if n & 1:
        print(0)
        return
    if any(x == "#" for x in (up[0], down[-1])):
        print(0)
        return
    if any(x == "#" for x in mid):
        print(0)
        return
    if n == 2:
        print(1)
        return
    up = up[1:-1]
    mid = mid[1:-1]
    down = down[1:-1]
    ans = 1
    for i in range(0, n - 2, 2):
        choice = 2
        if "#" in up[i:i+2]:
            choice -= 1
        if "#" in down[i:i+2]:
            choice -= 1
        if choice == 0:
            print(0)
            return
        ans = (ans * choice) % MOD
    print(ans)

for T in range(int(input())):
    print(f"Case #{T+1}:", end=" ")
    solve()
