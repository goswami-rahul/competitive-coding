import sys

def solve20():
  
  filled = set()
  while len(filled) != 9:
    sys.stdout.write("2 2\n")
    sys.stdout.flush()
    i = sys.stdin.readline()
    filled.add(i)
  
  filled = set()
  while len(filled) != 9:
    sys.stdout.write("2 5\n")
    sys.stdout.flush()
    i = sys.stdin.readline()
    filled.add(i)
  
  while len(filled) != 12:
    sys.stdout.write("2 6\n")
    sys.stdout.flush()
    i = sys.stdin.readline()
    if i == '0 0': return
    filled.add(i)

def solve200():
  
  points = [(2, 2), (2, 5), (2, 8), (2, 11), (2, 14), (2, 17), (5, 2), (5, 5), (5, 8), (5, 11), (5, 14), (5, 17), (8, 2), (8, 5), (8, 8), (8, 11), (8, 14), (8, 17), (11, 2), (11, 5), (11, 8), (11, 11), (11, 14), (11, 17)]
  for i, j in points:
    filled = set()
    while len(filled) != 9:
      print(i, j)
      sys.stdout.flush()
      x = sys.stdin.readline()
      if x == '0 0': return
      filled.add(x)

for t in range(int(input())):
  a = int(input())
  if a == 20:
    solve20()
  elif a == 200:
    solve200()
  else:
    sys.stderr.write("uh-oh\n")
