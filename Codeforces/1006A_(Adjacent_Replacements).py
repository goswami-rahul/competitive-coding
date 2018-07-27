input()
arr = list(map(int, input().split()))
print(*(e if e % 2 else e - 1 for e in arr))
