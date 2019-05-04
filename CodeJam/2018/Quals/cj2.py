def tsort(arr):
  done = False
  while not done:
    done = True
    for i in range(len(arr)-2):
      if arr[i] > arr[i+2]:
        done = False
        arr[i], arr[i+2] = arr[i+2], arr[i]
  for i in range(len(arr)-1):
    if arr[i] > arr[i+1]:
      return i
  return -1
  
for t in range(1, int(input())+1):
  input()
  arr = list(map(int, input().split()))
  i = tsort(arr)
  if i == -1:
    print("Case #{}: OK".format(t))
  else:
    print("Case #{}: {}".format(t, i))
