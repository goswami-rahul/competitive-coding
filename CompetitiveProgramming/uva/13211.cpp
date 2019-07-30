/**
 * We reverse the problem as adding vertices to the graph.
 * First, reorder the vertices in the order they are added.
 * consider dp[i][j] = shortest path from i to j
 * let the dp be calculated for n-1 vertices, and we have to add nth vertex.
 * We can find shortest path from n to all the previous vertices in O(v^2)
 * similarly,, We can find shortest path from all the previous vertices to n in O(v^2)
 * Now, it remains to update the dp of paths that start from some i-1 vetices,
 * and end in them. Such paths can only be updated by the new vertex n,
 * so loop over all pairs of previous vertices, and minimize it using
 * the dp calculated just before.
 * total complexity - O(n^3)
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
void err(istream_iterator<string>) { cerr << endl; }
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << "; "; err(++it, args...); }
template<typename T> void orz(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
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
    vector<vector<int>> w(n, vector<int>(n));
    for (auto &vec : w) for (int &z : vec) cin >> z;
    {
      vector<int> xs(n);
      for (int &x : xs) cin >> x;
      reverse(ALL(xs));
      auto nw = w;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          nw[i][j] = w[xs[i]][xs[j]];
        }
      }
      w = move(nw);
    }
    vector<vector<int>> dp(n, vector<int>(n, MOD));
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
      dp[i][i] = 0;
      for (int j = 0; j < i; ++j) {
        for (int k = 0; k < i; ++k) {
          uin(dp[i][k], w[i][j] + dp[j][k]);
          uin(dp[k][i], w[j][i] + dp[k][j]);
        }
      }
      for (int j = 0; j < i; ++j) {
        for (int k = 0; k < i; ++k) {
          uin(dp[j][k], dp[j][i] + dp[i][k]);
        }
      }
      for (int j = 0; j <= i; ++j) {
        for (int k = 0; k <= i; ++k) {
          ans += dp[j][k];
        }
      }
    }
    cout << ans << '\n';
  }
    
  return 0;
}
