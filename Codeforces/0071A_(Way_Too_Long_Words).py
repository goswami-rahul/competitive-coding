for _ in range(int(input())):
    s = input()
    a = len(s)
    if a <= 10:
        print(s)
    else:
        print(s[0] + str(a - 2) + s[-1])
