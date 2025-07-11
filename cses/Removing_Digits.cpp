#include<bits/stdc++.h>
using namespace std;
 
int main() {
  int n; cin >> n;
  vector<int> a(n + 1, 2e9);
  a[0] = 0;
  for (int i = 1; i <= n; ++i) {
    int d = i;
    while (d) {
      a[i] = min(a[i], 1 + a[i - d % 10]);
      d /= 10;
    }
  }
  cout << a[n];
}
