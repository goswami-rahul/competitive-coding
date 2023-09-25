#ifdef Rahul
#include "RAHUL.h"
#else
#include <bits/stdc++.h>
using namespace std;
#define error(...) 42;
#endif
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
using i64 = int64_t;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
const int MOD = (int) 1e9 + 7;
const i64 INF = (i64) 1e18 + 42;

vector<int> PrefixFn(const vector<int> &s) {
  vector<int> pi(s.size());
  for (int i = 1; i < (int) s.size(); ++i) {
    int p = pi[i - 1];
    while (p > 0 && s[i] != s[p]) p = pi[p - 1];
    if (s[i] == s[p]) pi[i] = 1 + p;
  }
  return pi;
}

bool SolveCase() {
  int n, k; cin >> n >> k;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  if (n == 2) k %= 2;
  if (k == 0) return a == b;
  b.push_back(-42);
  for (int i = 0; i < 2 * n - 1; ++i) {
    b.push_back(a[i % n]);
  }
  auto p = PrefixFn(b);
  for (int i = 2 * n + (k == 1); i < b.size(); ++i) {
    if (p[i] == n) return true;
  }
  return false;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    error(t)
    cout << "Case #" << t << ": " << (SolveCase() ? "YES\n" : "NO\n");
  }
} 