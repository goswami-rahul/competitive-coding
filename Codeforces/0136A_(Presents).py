n = int(input())
arr = list(map(int, input().split()))
print(*(arr.index(e + 1) + 1 for e in range(n)))
