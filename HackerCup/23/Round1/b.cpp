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

vector<int> fs;
vector<int> ans;
vector<int> cur;

void Rec(int i, int s) {
  if (s < 0) return;
  if (i == -1 && s == 0) {
    if (ans.empty()) ans = cur;
    else if (cur.size() < ans.size()) ans = cur;
    return;
  }
  if (i == -1 && s > 0) {
    while (s--) {
      cur.push_back(1);
    }
    if (ans.empty()) ans = cur;
    else if (cur.size() < ans.size()) ans = cur;
    return;
  }
  if (s == 0) return;
  cur.push_back(fs[i]);
  Rec(i - 1, s - fs[i]);
  cur.pop_back();
  if (!cur.empty()) {
    int d = cur.back() * fs[i] - cur.back();
    cur.back() *= fs[i];
    Rec(i - 1, s - d);
    cur.back() /= fs[i];
  }
}

void SolveCase() {
  int u; cin >> u;
  int p = u;
  fs.clear();
  ans.clear();
  cur.clear();
  for (int i = 2; i < 42; ++i) {
    while (p % i == 0) {
      fs.push_back(i);
      p /= i;
    }
  }
  if (p > 41) {
    cout << "-1\n";
    return;
  }
  assert(p == 1);
  int sum = 0;
  for (int x : fs) sum += x;
  if (sum > 41) {
    cout << "-1\n";
    return;
  }
  reverse(ALL(fs));
  Rec(fs.size() - 1, 41);
  if (ans.empty()) {
    cout << "-1\n";
  } else {
    cout << ans.size() << ' ';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
  }
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 