/**
 * choose the directions greedily with smallest first, if it is possible 
 * to reach the destination in remaining steps.
 * To check it in constant time, precompute shortest distance to every point
 * using bfs/dfs.
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
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
int n, m;
vector<string> a;
vector<vector<int>> dis;
bool good(int i, int j) {
  return 0 <= i && i < n && j >= 0 && j < m && a[i][j] != '*';
}
void go(int i, int j, int r, string &s) {
  if (r == 0) return;
  if (good(i + 1, j) && dis[i + 1][j] <= r - 1) {
    s += 'D';
    go(i + 1, j, r - 1, s);
  } else if (good(i, j - 1) && dis[i][j - 1] <= r - 1) {
    s += 'L';
    go(i, j - 1, r - 1, s);
  } else if (good(i, j + 1) && dis[i][j + 1] <= r - 1) {
    s += 'R';
    go(i, j + 1, r - 1, s);
  } else if (good(i - 1, j) && dis[i - 1][j] <= r - 1) {
    s += 'U';
    go(i - 1, j, r - 1, s);
  } else {
    kek("IMPOSSIBLE");
  }
}
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int k;
  cin >> n >> m >> k;
  a.resize(n);
  for (string &s : a) {
    cin >> s;
  }
  dis.assign(n, vector<int>(m, MOD));
  int x = -1, y = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == 'X') {
        x = i, y = j;
        break;
      }
    }
  }
  dis[x][y] = 0;
  vector<int> que;
  int fp = 0;
  que.push_back(x << 10 | y);
  const int dx[] = {1, -1, 0, 0};
  const int dy[] = {0, 0, 1, -1};
  while (SZ(que) > fp) {
    int ux = que[fp++], uy = ux & ((1 << 10) - 1);
    ux >>= 10;
    for (int i = 0; i < 4; ++i) {
      if (good(ux + dx[i], uy + dy[i]) && uin(dis[ux + dx[i]][uy + dy[i]], 1 + dis[ux][uy])) {
        que.push_back((ux + dx[i]) << 10 | (uy + dy[i]));
      }
    }
  }
  if (k & 1) kek("IMPOSSIBLE");
  
  string ans;
  go(x, y, k, ans);
  kek(ans);
  
  return 0;
}
