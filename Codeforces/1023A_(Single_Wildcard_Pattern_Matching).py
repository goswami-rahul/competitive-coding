def solve():
    n, m = map(int, input().split())
    s = input()
    t = input()
    m = len(t)
    if "*" not in s:
        if s == t:
            print("YES")
        else:
            print("NO")
        return
    a, b = s.split("*")
    # print(a, b)
    if len(a) + len(b) > m:
        print("NO")
        return
    b = b[::-1]
    k = t[::-1]
    # print(b, k)
    if a == t[:len(a)] and b == k[:len(b)]:
        print("YES")
    else:
        print("NO")


solve()
