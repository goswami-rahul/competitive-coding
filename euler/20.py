n = 100
ans = 1
while n:
  ans *= n
  n -= 1
print(sum(int(c) for c in str(ans)))
