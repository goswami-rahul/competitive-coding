a, b, x = map(int, input().split())
k = x + 1
if k % 2 == 0:
    s = "0" * (a - k//2) + "01" * (k//2) + "1" * (b - k//2)
else:
    if a > b:
        s = "01" * (k//2) + "1" * (b - k//2) + "0" * (a - k//2)
    else:
        s = "1" * (b - k//2) + "0" * (a - k//2) + "01" * (k//2)
print(s)
