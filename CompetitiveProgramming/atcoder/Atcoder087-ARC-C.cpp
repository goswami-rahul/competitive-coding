/**
 * Inserting the strings in a trie, we can notice that inserting
 * a string in a binary tree forbids a complete binary tree, and the path 
 * from the current root till this node.
 * This creates 0 or more new independent complete binary trees, smaller
 * than current tree. 
 * We can calculate grundy of binary tree of height h, and thus use Grumdy theorem
 * in all the independent initial states.
 * Grundy simulation with small states gives the grundy as the lowest set bit in h.
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
void err(istream_iterator<string>) {}
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2> buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (const auto e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
struct Trie {
  struct Node {
    static const int ALPHA = 2;
    bool is;
    array<int,ALPHA> nxt;
    int depth;
    Node(): is(), nxt(), depth() {}
    int& operator [] (size_t idx) {
      return nxt[idx];
    }
  };
  vector<Node> nodes;
  int ptr = 1;
  Trie(const int nax = 2e5): nodes(nax) {}
  bool add(const string &s) {
    int cur = 0;
    for (const char &c: s) {
      int u = c - '0';
      if (!nodes[cur][u]) {
        nodes[ptr].depth = 1 + nodes[cur].depth;
        nodes[cur][u] = ptr++;
      }
      cur = nodes[cur][u];
    }
    if (nodes[cur].is) return false;
    return nodes[cur].is = true;
  }
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  i64 L;
  cin >> n >> L;
  Trie trie(1e5 + 42);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    trie.add(s);
  }
  vector<i64> a;
  for (int i = 0; i < trie.ptr; ++i) {
    int cnt = 0;
    for (int v: trie.nodes[i].nxt) cnt += !v;
    if (cnt == 1) a.push_back(L - trie.nodes[i].depth);
  }
  i64 g = 0;
  for (i64 x: a) {
    for (int b = 0; ; ++b) if (x >> b & 1) {
      g ^= 1LL << b;
      break;
    }
  }
  cout << (g ? "Alice\n" : "Bob\n");
  /*
  {
    vector<int> g(42);
    for (int i = 0; i < 42; ++i) {
      vector<bool> has(100);
      int xr = 0; has[0] = true;
      for (int j = i - 1; ~j; --j) {
        xr ^= g[j];
        has[xr] = true;
      }
      while (has[g[i]]) ++g[i];
      printf("i = %d, g = %d\n", i + 1, g[i]);
    }
  }
  */

  return 0;
} 
/**
 * P G
 * - 0
 * 0 1
 * 1 2  (-> 0, 1)
 * 2 1  (-> 0, 2, 2 ^ 1)
 * 3 4  (-> 0, 1, 1 ^ 2, 1 ^ 2 ^ 1)
 * 4 1  (-> 0, 4, 4 ^ 1, 4 ^ 1 ^ 2, 4 ^ 1 ^ 2 ^ 1)
**/
