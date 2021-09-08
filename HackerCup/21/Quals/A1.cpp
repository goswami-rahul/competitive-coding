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

const int K = 26;

bool Vowel(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';  
}

void SolveCase() {
  string s; cin >> s;
  vector<vector<int>> dis(K, vector<int>(K, MOD));
  for (int i = 0; i < K; ++i) dis[i][i] = 0;
  for (int i = 0; i < K; ++i) 
    for (int j = 0; j < K; ++j) 
      if (Vowel(i + 'A') != Vowel(j + 'A'))
        dis[i][j] = 1;
  for (int k = 0; k < K; ++k) 
    for (int i = 0; i < K; ++i) 
      for (int j = 0; j < K; ++j) 
        uin(dis[i][j], dis[i][k] + dis[k][j]);
  int ans = MOD;
  error(dis);
  for (int i = 0; i < K; ++i) {
    int cur = 0;
    for (char c : s) {
      cur += dis[c - 'A'][i];
      if (cur >= MOD) break;
    }
    uin(ans, cur);
  }
  if (ans == MOD) ans = -1;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 