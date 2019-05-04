reads = lambda: [int(x) for x in input().split()]
read = lambda: int(input())
import sys

B = 56
def test_case():
  a = []
  ask = B * 4
  print(ask, flush=True)
  ans = read()
  a = []
  for x in range(101):
    for y in range(101):
      for z in range(101):
        if ans == (x << (ask // 6)) + (y << (ask // 5)) + (z << (ask // 4)):
          a.append([x, y, z])
  a, = a
  ask = B
  print(ask, flush=True)
  r = read()
  r -= (a[0] << (ask // 6)) + (a[1] << (ask // 5)) + (a[2] << (ask // 4))
  for x in range(101):
    for y in range(101):
      for z in range(101):
        if r == (x << (ask // 3)) + (y << (ask // 2)) + (z << ask):
          print(z, y, x, *a[::-1], flush=True)
          break
  
  ver = read()
  if ver == -1:
    exit()
  return

T, W = reads()
for tno in range(1, T + 1):
  test_case()
