input()
def f(s):
    return "".join(sorted(set(s)))
arr = set(map(f, input().split()))
print(len(arr))
