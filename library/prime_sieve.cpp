const int M = 1e6 + 42;
array<int, M> lpf;
auto primes = [](){
  vector<int> p;
  iota(lpf.begin(), lpf.end(), 0);
  for (int i = 2; i < M; ++i) {
    if (lpf[i] == i) {
      p.push_back(i);
      for (int j = i + i; j < M; j += i) {
        if (lpf[j] == j) lpf[j] = i;
      }
    }
  }
  return p;
}();
