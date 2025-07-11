#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  long long ans = -1;
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    long long x;
    cin >> x;
    ans = max(ans, x);
    sum += x;
  }
  cout << max(2 * ans, sum);
}
