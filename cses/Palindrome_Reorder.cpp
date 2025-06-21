#include<bits/stdc++.h>

int main() {
  std::string s; 
  std::cin >> s;
  std::array<int, 26> cnt{};
  for (char c : s) cnt[c - 'A']++;
  int odds = std::count_if(cnt.begin(), cnt.end(), [](int x) { return x % 2; });
  if (odds > 1) {
    std::cout << "NO SOLUTION\n";
  } else {
    int i = 0;
    for (auto d : cnt) {
      if (d % 2 == 0) {
        std::cout << std::string(d / 2, (char)(i + 'A'));
      }
      ++i;
    }
    i = 0; 
    for (auto d : cnt) {
      if (d % 2 == 1) {
        std::cout << std::string(d, (char)(i + 'A'));
      }
      ++i;
    }
    std::reverse(cnt.begin(), cnt.end());
    i = 26;
    for (auto d : cnt) {
      --i;
      if (d % 2 == 0) {
        std::cout << std::string(d/  2, (char)(i + 'A'));
      }
    } 
  }
}
