ans = 10000
for i in range(0, 10000):
    ok = False
    for itr in range(50):
        i += int(str(i)[::-1])
        if str(i) == str(i)[::-1]:
            ans -= 1
            break
print(ans)
