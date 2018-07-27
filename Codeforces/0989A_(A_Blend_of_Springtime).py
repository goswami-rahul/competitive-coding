s = input()
if len(s) <= 2:
    print("No")
else:
    for i in range(1, len(s) - 1):
        t = "".join(sorted(s[i-1:i+2]))
        # print(t)
        if t == "ABC":
            print("Yes")
            break
    else:
        print("No")
