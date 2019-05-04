def test_case(tno):
    s = input()
    a = ""
    b = ""
    for c in s:
        if c == '4':
            a += '3'
            b += '1'
        else:
            a += c
            b += '0'
    print("Case #{}: {} {}".format(tno, a, b))

for i in range(int(input())):
    test_case(i + 1)