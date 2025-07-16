#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;;
inline int add(int a, int b, int mod = MOD) {
  a += b; return a >= mod ? a - mod : a;
}
inline int sub(int a, int b, int mod = MOD) {
  a -= b; return a < 0 ? a + mod : a;
}
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline int mpow(int base, long long ex, int mod = MOD) {
  int res = 1;
  for (; ex > 0; ex >>= 1) {
    if (ex & 1) res = mul(res, base, mod);
    base = mul(base, base, mod);
  }
  return res;
}
inline int inv(int a, int mod = MOD) {
  return mpow(a, mod - 2, mod);
}
inline int mdiv(int a, int b, int mod = MOD) {
  return mul(a, mpow(b, mod - 2,  mod));
}
inline void adds(int &a, int b, int mod = MOD) {
  a += b; if (a >= mod) a -= mod;
}
inline void subs(int &a, int b, int mod = MOD) {
  a -= b; if (a < 0) a += mod;
}
inline void muls(int &a, int b, int mod = MOD) {
  a = int((long long) a * b % mod);
}
inline void mdivs(int &a, int b, int mod = MOD) {
  a = mdiv(a, b, mod);
}

int main() {
  int n, m; cin >> n >> m;
  vector<int> dp(m + 2);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    vector<int> np(m + 2);
    for (int j = 1; j <= m; ++j) {
      if (x == j || x == 0) {
        np[j] = add(dp[j], add(dp[j - 1], dp[j + 1]));
        if (i == 0) np[j] = 1;
      }
    }
    dp = move(np);
  }
  int sum = 0;
  for (int x : dp) adds(sum, x);
  cout << sum;
}
