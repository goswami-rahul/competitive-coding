#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, x; cin >> n >> x;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  sort(a.begin(), a.end());
  int i = 0, j = n - 1;
  while (i <= j) {
    if (a[i] + a[j] <= x) {
      i++;
    }
    --j;
  }
  cout << n - j - 1 << '\n';
}
