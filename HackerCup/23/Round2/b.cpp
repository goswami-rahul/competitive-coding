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

vector<int> Zfn(vector<int> s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

vector<int> ManOdd(vector<int> s) {
    int n = s.size();
    s.insert(s.begin(), -2);
    s.insert(s.end(), -3);
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> Manacher(vector<int> s) {
    vector<int> t;
    for(auto c : s) {
      t.push_back(-5);
      t.push_back(c);
    }
    t.push_back(-5);
    auto res = ManOdd(t);
    return vector<int>(begin(res) + 1, end(res) - 1);
}

int SolveCase() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  // reverse(ALL(b));
  for (int x : a) b.push_back(x);
  for (int x : b) a.push_back(x);
  auto m = Manacher(a);
  assert (SZ(m) == 2 * SZ(a) - 1);
  vector<int> meve, modd;
  for (int i = 0; i < m.size(); ++i) {
    if (i % 2) {
      meve.push_back(min(2 * n, m[i] - 1));
    } else {
      modd.push_back(min(2 * n, m[i] - 1));
    }
  }
  int ans = MOD;
  int cnt = 0;
  for (int i = 0; i < meve.size(); ++i) if (meve[i] == 2 * n) {
    if (++cnt > 100) break;
    int ok = 1, rok = 1;
    for (int j = 0; j < n; ++j) {
      int f = (i - n + 1) + j;
      int s = (i + 1) + j;
      if (n % 2 == 0) {
        if (j < n / 2) {
          ok &= a[f] < a[s];
          rok &= a[s] < a[f];
        } else {
          rok &= a[f] < a[s];
          ok &= a[s] < a[f];
        }
      } else {
        if (j < n / 2) {
          ok &= a[f] < a[s];
          rok &= a[s] < a[f];
        } else if (j > n / 2) {
          rok &= a[f] < a[s];
          ok &= a[s] < a[f];
        }
      }
    }
    if (ok) uin(ans, i - n + 1);
    if (rok) uin(ans, i + 1);
  }
  assert (cnt < 3);
  if (ans == MOD) ans = -1;
  return ans;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    error(t)
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 