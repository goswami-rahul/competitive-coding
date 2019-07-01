#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
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
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/
const int x = 2, X = 3;
string s;
int ptr;

struct Exp {
  char op;
  int val;
  Exp *lhs;
  Exp *rhs;
  Exp() = default;
  void parse() {
    if (s[ptr] != '(') {
      op = '.';
      if (s[ptr] == '0') val = 0;
      if (s[ptr] == '1') val = 1;
      if (s[ptr] == 'x') val = x;
      if (s[ptr] == 'X') val = X;
      ptr++;
    } else {
      ptr++;
      lhs = new Exp();
      lhs->parse();
      op = s[ptr++];
      rhs = new Exp();
      rhs->parse();
      assert (s[ptr] == ')');
      ptr++;
      eval();
      delete lhs;
      delete rhs;
    }
  }
  void eval() {
    assert (op != '.');
    if (op == '|') {
      int lval = lhs->val, rval = rhs->val;
      if (lval == 1 || rval == 1) val = 1;
      else if (lval == 0) val = rval;
      else if (rval == 0) val = lval;
      else if (lval != rval) val = 1;
      else val = rval; 
    }
    if (op == '&') {
      int lval = lhs->val, rval = rhs->val;
      if (lval == 0 || rval == 0) val = 0;
      else if (lval == 1) val = rval;
      else if (rval == 1) val = lval;
      else if (lval != rval) val = 0;
      else val = rval; 
    }
    if (op == '^') {
      int lval = lhs->val, rval = rhs->val;
      val = lval ^ rval;
    }
  }
};

void test_case() {
  cin >> s;
  ptr = 0;
  Exp e;
  e.parse();
  cout << (e.val >> 1 & 1) << '\n';
}

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    test_case();
  }
  
  
  return 0;
}
