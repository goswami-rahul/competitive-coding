#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
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

const int N = 1005;
string grid[N];
int dp[N][N];

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> grid[i];
  dp[0][0] = grid[0][0] == '.';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) if (grid[i][j] == '.') {
      if (i) adds(dp[i][j], dp[i - 1][j]);
      if (j) adds(dp[i][j], dp[i][j - 1]);
    }
  }
  cout << dp[n - 1][n - 1];
}
