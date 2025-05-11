#include <bits/stdc++.h>

int main() {
  std::string s;
  std::cin >> s;
  std::string t = s;
  std::map<char, int> cnt{};
  for (char c : s) ++cnt[c];
  for (auto [c, k] : cnt) {
  }
}