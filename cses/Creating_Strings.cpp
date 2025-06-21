#include<bits/stdc++.h>

int main() {
  std::string s; 
  std::cin >> s;
  std::vector<std::string> ans;
  std::sort(s.begin(), s.end());
  do {
    ans.push_back(s);
  } while (std::next_permutation(s.begin(), s.end()));
  std::cout << ans.size() << '\n';
  for (auto s : ans) std::cout << s << '\n';
}
