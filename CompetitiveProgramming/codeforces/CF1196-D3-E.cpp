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
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int tt;
  cin >> tt;
  while (tt--) {
    int b, w;
    cin >> b >> w;
    int y = 3;
    if (b > w) {
      y++;
      swap(b, w);
    }
    vector<pair<int,int>> ans;
    for (int i = 2, j = 0; j < b; ++j, i += 2) {
      ans.emplace_back(i, y);
    }
    for (int i = 3, j = 0; j < b - 1 && w > 0; i += 2, ++j, --w) {
      ans.emplace_back(i, y);
    }
    for (int i = 2, j = 0; j < b && w > 0; --w, i += 2, ++j) {
      ans.emplace_back(i, y + 1);
    }
    for (int i = 2, j = 0; j < b && w > 0; --w, i += 2, ++j) {
      ans.emplace_back(i, y - 1);
    }
    if (w > 0) {
      --w;
      ans.emplace_back(1, y);
    }
    if (w > 0) {
      --w;
      ans.emplace_back(2 * b + 1, y);
    }
    if (w > 0) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
      for (const auto &[u, v] : ans) {
        cout << u << " " << v << '\n';
      }
    }
  }
  
  return 0;
}
