vector<int> prefix_function(const string &s) {
  vector<int> pi(s.size());
  for (int i = 1; i < (int) s.size(); ++i) {
    int p = pi[i - 1];
    while (p > 0 && s[i] != s[p]) p = pi[p - 1];
    if (s[i] == s[p]) ans = 1 + p;
  }
  return pi;
}
