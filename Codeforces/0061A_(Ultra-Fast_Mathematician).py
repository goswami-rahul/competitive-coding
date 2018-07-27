a = input()
b = input()
ans = ""
for aa, bb in zip(a, b):
    if aa == bb:
        ans += "0"
    else:
        ans += "1"
print(ans)
