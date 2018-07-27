
def solve():
    n = int(input())
    a = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    if (1 in A) or (1 in B):
        print(-1)
        return
    z = A[0], A[-1], B[0], B[-1]
    x = 1
    for e in A[1:-1]:
        x *= e/(e-1)
    y = 1
    for e in B[1:-1]:
        y *= e/(e-1)
    p = 1
    for e in z:
        p *= e/(e-1)
    print(a * (p * (x) * (y) - 1))

solve()
