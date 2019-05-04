import math

def solve(a, t):
  
  l = (a - math.sqrt(2 - a*a))/2
  x1 = (a - l)/2
  y1 = -math.sqrt(0.25 - x1*x1)
  
  x2 = l/2
  y2 = x1
  
  print("Case #{}:".format(t))
  print(x1, y1, 0)
  print(x2, y2, 0)
  print(0, 0, 0.5)
  

for t in range(1, int(input())+1):
  a = float(input())
  solve(a, t)
