s = input()
if s[-1] not in "aeioun":
    ans = "NO"
else:
    ans = "YES"
    for i in range(len(s) - 1):
        if s[i] not in "aeioun":
            if s[i + 1] not in "aeiou":
                ans = "NO"
print(ans)
