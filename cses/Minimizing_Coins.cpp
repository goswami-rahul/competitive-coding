#include<bits/stdc++.h>
using namespace std;
 
int main() {
  int n, m; cin >> n >> m;
  vector<int> coins(n);
  for (int &x : coins) cin >> x;
  const int inf = 2e9;
  vector<int> a(m + 1, inf);
  a[0] = 0;
  for (int i = 1; i <= m; ++i) {
    for (int x : coins) if (i >= x) 
      a[i] = min(a[i], 1 + a[i - x]);
  }
  if (a[m] == inf) a[m] = -1;
  cout << a[m];
