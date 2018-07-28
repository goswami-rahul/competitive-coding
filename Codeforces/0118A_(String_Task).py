s = input()
a = ""
for c in s:
    if c in "aeiouyAEIOUY":
        continue
    c = c.lower()
    a += "." + c
print(a)
