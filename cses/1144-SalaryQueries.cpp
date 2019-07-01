#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
 
#define N 200001
 
using namespace std;
static int a[N], Q[N][3], b[N + N], fen[N + N];
 
int main()
{
  int n, q, m = 0;
  scanf(" %d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf(" %d", a + i);
    b[m++] = a[i];
  }
  for (int i = 0; i < q; ++i) {
    char c;
    scanf(" %c %d %d", &c, &Q[i][1], &Q[i][2]);
    if (c == '?') {
      Q[i][0] = 1;
    } else {
      b[m++] = Q[i][2];
    }
  }
  sort(b, b + m);
  m = unique(b, b + m) - b;
  for (int i = 0; i < n; ++i) {
    a[i] = upper_bound(b, b + m, a[i]) - b;
    fen[a[i]]++;
  }
  for (int i = 1; i <= m; ++i) if (i + (i & -i) <= m) {
    fen[i + (i & -i)] += fen[i];
  }
  for (int i = 0; i < q; ++i) {
    if (Q[i][0] == 1) {
      int res = 0, pos;
      pos = upper_bound(b, b + m, Q[i][2]) - b;
      for (; pos > 0; pos -= pos & -pos)
        res += fen[pos];
      pos = lower_bound(b, b + m, Q[i][1]) - b;
      for (; pos > 0; pos -= pos & -pos)
        res -= fen[pos];
      printf("%d\n", res);
    } else {
      for (int pos = a[Q[i][1] - 1]; pos <= m; pos += pos & -pos)
        fen[pos]--;
      for (int pos = a[Q[i][1] - 1] = upper_bound(b, b + m, Q[i][2]) - b; pos <= m; pos += pos & -pos)
        fen[pos]++;
    }
  }
  
  return 0;
}
