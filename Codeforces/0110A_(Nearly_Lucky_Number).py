n = input()
a = str(sum(e == '4' or e == '7' for e in n))
print("YES" if all(e == '4' or e == '7' for e in a) else "NO")
