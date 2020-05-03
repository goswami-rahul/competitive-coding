#include <bits/stdc++.h>
using namespace std;

int calc(int x, int a, int b) {
  int val = x * x + a * x + b;
  if (val < 0) val = 0;
  return val;
}
int32_t main(int argc, char * argv[]) {
  cin.tie(nullptr) -> sync_with_stdio(false);
  (void) argc; (void) argv;
  
  const int A = 999, B = 1000, N = B << 4;
  vector<int> prime(N, 1);
  prime[0] = prime[1] = 0;
  for (int i = 2; i < N; ++i) if (prime[i]) {
    for (int j = i; (j += i) < N; ) prime[j] = 0;
  }
  int ans = 0, prod = 0;
  for (int a = -A; a <= A; ++a) for (int b = -B; b <= B; ++b) {
    int x = 0;
    while (prime[calc(x, a, b)]) ++x;
    if (x > ans) ans = x, prod = a * b;
  }
  cout << ans << " " << prod << endl;
}
