def test_case():
    input()
    s = input()
    a = ""
    for c in s:
        a += "E" if c == "S" else "S"
    return a
for i in range(int(input())):
    print("Case #{}: {}".format(i + 1, test_case()))