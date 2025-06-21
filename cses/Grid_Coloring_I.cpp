#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  string p = string(m, 'A');
  for (int i = 1; i <= n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < m; ++j) {
      char c = 'A';
      while (c == s[j] || (j && c == s[j-1]) || c == p[j]) ++c;
      s[j] = c;
    }
    cout << s << '\n';
    p = move(s);
  }
}
