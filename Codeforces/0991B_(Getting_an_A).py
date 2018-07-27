# a, b, c, n = map(int, input().split())
n = int(input())
arr = sorted(map(int, input().split()))
i = 0
while sum(arr) < 4.5 * n:
    arr[i] = 5
    i += 1
print(i)
