s = input()
if len(set(s)) == 1:
    print(0)
else:
    if s == s[::-1]:
        print(len(s)-1)
    else:
        print(len(s))
