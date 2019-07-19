/**
 * The greedy solution is to find any horizontal or vertical line which 
 * separates the field into two, and solve them recursively.
 * This will be O(n^2).
 * To optimize the solution, we check for partition from all 4 directions
 * parallely, so one part has size atmost half, and we take O(size of small)
 * to find it.
 * Once we find it, we solve it recursively, and delete those from our
 * current sets, continue solving current sets.
 * The implementation can be tricky, I use std::list to delete arbritrarily.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
string to_string(char c) { return "'" + string(1, c) + "'";}
string to_string(string s) { return '"' + s + '"';}
string to_string(const char* s) { return to_string((string) s);}
template<typename A> string to_string(A);
template<typename A, typename B> string to_string(pair<A, B> p){
  return "(" + to_string(p.first) + ": " + to_string(p.second) + ")";}
template<typename A> string to_string(A v) {bool f = false; string r = "{"; 
  for (auto x: v) {if (f) r += ", "; r += to_string(x); f = true;} return r += "}";}
template<typename A> string to_string(vector<vector<A>> v) {string r; 
  for (auto x: v) r += "\n" + to_string(x); return r;}
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 998244353;
long long const INF = 1e18;
/***********************************************************************/
struct rect {
  int x1, x2, y1, y2, i;
  bool operator < (const rect& rhs) const {
    return i < rhs.i;
  }
};
string to_string(rect r) {
  return "<(" + to_string(r.x1) + ", " + to_string(r.y1) + "), (" + 
    to_string(r.x2) + ", " + to_string(r.y2) + ")>";
}
bool go(const vector<rect> &A) {
  if (SZ(A) == 1) return true;
  list<rect> lftx(ALL(A)), rgtx(ALL(A)), lfty(ALL(A)), rgty(ALL(A));
  lftx.sort([] (const auto &a, const auto &b) {
    return a.x1 < b.x1;
  });
  rgtx.sort([] (const auto &a, const auto &b) {
    return a.x2 > b.x2;
  });
  lfty.sort([] (const auto &a, const auto &b) {
    return a.y1 < b.y1;
  });
  rgty.sort([] (const auto &a, const auto &b) {
    return a.y2 > b.y2;
  });
  set<int> seen;
  while (SZ(seen) < SZ(A) - 1) {
    auto ilx = lftx.begin();
    auto irx = rgtx.begin();
    auto ily = lfty.begin();
    auto iry = rgty.begin();
    auto clean = [&] () {
      while (ilx != lftx.end() && seen.count(ilx->i)) ilx = lftx.erase(ilx);
      while (irx != rgtx.end() && seen.count(irx->i)) irx = rgtx.erase(irx);
      while (ily != lfty.end() && seen.count(ily->i)) ily = lfty.erase(ily);
      while (iry != rgty.end() && seen.count(iry->i)) iry = rgty.erase(iry);
      return true;
    };
    clean();
    int lboundx = lftx.front().x2;
    int rboundx = rgtx.front().x1;
    int lboundy = lfty.front().y2;
    int rboundy = rgty.front().y1;
    ilx++; irx++; ily++; iry++;
    bool found = false;
    while (clean() && ilx != lftx.end()) {
      if (ilx->x1 >= lboundx) {
        auto it = lftx.begin();
        vector<rect> small;
        while (it != ilx) {
          small.push_back(*it);
          seen.insert(it->i); 
          it = lftx.erase(it);
        }
        if (!go(small)) return false;
        found = true; break;
      }
      if (irx->x2 <= rboundx) {
        auto it = rgtx.begin();
        vector<rect> small;
        while (it != irx) {
          small.push_back(*it);
          seen.insert(it->i); 
          it = rgtx.erase(it);
        }
        if (!go(small)) return false;
        found = true; break;
      }
      if (ily->y1 >= lboundy) {
        auto it = lfty.begin();
        vector<rect> small;
        while (it != ily) {
          small.push_back(*it);
          seen.insert(it->i); 
          it = lfty.erase(it);
        }
        if (!go(small)) return false;
        found = true; break;
      }
      if (iry->y2 <= rboundy) {
        auto it = rgty.begin();
        vector<rect> small;
        while (it != iry) {
          small.push_back(*it);
          seen.insert(it->i); 
          it = rgty.erase(it);
        }
        if (!go(small)) return false;
        found = true; break;
      }
      uax(lboundx, ilx->x2);
      uin(rboundx, irx->x1);
      uax(lboundy, ily->y2);
      uin(rboundy, iry->y1);
      ilx++; irx++; ily++; iry++;
    }
    if (!found) return false;
  }
  return true;
}

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vector<rect> a(n);
  int cnt = 0;
  for (auto &z: a) {
    cin >> z.x1 >> z.y1 >> z.x2 >> z.y2;
    z.i = cnt++;
  }
  cout << (go(a) ? "YES\n" : "NO\n");
  
  return 0;
}
