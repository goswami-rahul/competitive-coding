/**
 * Lets say we have two cost matrices denoting minimum cost from each node,
 * in exactly a and b steps, respectively. We can create a new matrix from
 * these two matrices, which has min cost for each i, j in exactly (a + b) steps.
 * So, we can calculate such matrix for any k in O(log k) using binary exponentiation.
 * Since, we need atleast k steps, maybe we can use some more steps to find even less cost.
 * For this, we can calculate all pair shortest paths using floyd warshall's.
 * and minimize the cost using this.
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
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
using Matrix = vector<vector<i64>>;
Matrix op(const Matrix &a, const Matrix &b) {
  const int n = (int) a.size();
  Matrix res(n, vector<i64>(n, INF));
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        uin(res[i][j], a[i][k] + b[k][j]); 
      }
    }
  }
  return res;
}
Matrix power(const Matrix &a, int k) {
  if (k == 1) return a;
  if (k & 1) return op(a, power(a, k - 1));
  return power(op(a, a), k >> 1);
}
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Region #" << t << ":\n";
    int K, n;
    cin >> K >> n;
    Matrix cost(n, vector<i64>(n));
    for (auto &v : cost) for (i64 &z : v) cin >> z;
    Matrix res = power(cost, K);
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          uin(cost[i][j], cost[i][k] + cost[k][j]); 
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          uin(res[i][j], res[i][k] + cost[k][j]);
        }
        cout << res[i][j] << " ";
      }
      cout << "\n";
    }
    
  }
  
  return 0;
}
