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
int const MOD = 1e5;
long long const INF = 1e18;
/***********************************************************************/

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    int rg = MOD, lf = -MOD, up = MOD, dn = -MOD; 
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      int z;
      cin >> z;
      if (z == 0) {
        uax(lf, x);
      }
      cin >> z;
      if (z == 0) {
        uin(up, y);
      }
      cin >> z;
      if (z == 0) {
        uin(rg, x);
      }
      cin >> z;
      if (z == 0) {
        uax(dn, y);
      }
    }
    if (lf > rg || dn > up) {
      cout << "0\n";
    } else {
      cout << "1 " << lf << " " << dn << '\n';
    }
  }
  
  return 0;
}
