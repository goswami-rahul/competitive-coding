#include<bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;
  int n = s.size();
  array<int, 26> a{};
  for (char c : s) {
    a[c - 'A']++;
  }
  s = string(n, '-');
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 26; ++j) {
      if (i > 0 && j + 'A' == s[i - 1]) {
        continue;
      }
      if (a[j] == 0) continue;
      --a[j];
      int m = *max_element(a.begin(), a.end());
      if (*max_element(a.begin(), a.end()) <= (n - i) / 2) {
        s[i] = j + 'A';
        break;
      }
      ++a[j];
    }
    if (s[i] == '-') {
      cout << "-1\n";
      return 0;
    }
  }
  cout << s << '\n';
}
