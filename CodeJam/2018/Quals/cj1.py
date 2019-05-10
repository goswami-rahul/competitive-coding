def solve(t, d, p):
  length = len(p)
  s = 1
  tot = 0
  cstack = []
  scount = 0
  for i, c in enumerate(p):
    if c == 'S':
      tot += s
      scount += 1
    else:
      s *= 2
      cstack.append(i)
  
  # only case for impossible
  if scount > d:
    print("Case #{}: IMPOSSIBLE".format(t))
    return
  
  steps = 0
  while cstack:
    
    if tot <= d:
      break
    
    top = cstack[-1]
    
    if top == length - 1:
      # C at last, it can be neglected.
      cstack.pop()
      length -= 1
    
    elif top < length - 1:
      tot = tot - 2**(len(cstack)-1)
      cstack[-1] += 1
      steps += 1
    
    else:
      print("uh-oh")
      
  
  if tot > d:
    print("uh-oh-2")
  else:
    print("Case #{}: {}".format(t, steps))
for t in range(1, int(input())+1):
  d, p = input().split()
  d = int(d)
  solve(t, d, p)
