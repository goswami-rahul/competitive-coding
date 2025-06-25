#include<bits/stdc++.h>
using namespace std;

int main() {
  int q; cin >> q;
  while (q--) {
    long long k; cin >> k;
    --k;
    long long p = 9, t = 1;
    int len = 1;
    while (k >= p * len) {
      k -= p * len;
      p *= 10;
      t *= 10;
      ++len;
    }
    long long n = k / len + t;
    int offset = len - 1 - k % len;
    while (offset > 0) {
      --offset;
      n /= 10;
    }
    cout << n % 10 << '\n';
  }
}
