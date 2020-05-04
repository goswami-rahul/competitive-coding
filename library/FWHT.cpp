template<typename T>
void FWHT(vector<T> &vals, bool inverse) {
  int n = (int) vals.size();
  while (n & (n - 1)) n = (n | (n - 1)) + 1;
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        const T u = vals[i + j], v = vals[i + len + j];
        vals[i + j] = u + v;
        vals[i + len + j] = u - v;
      }
    }
  }
  if (inverse) {
    for (int i = 0; i < n; ++i) {
      vals[i] /= n;
    }
  }
}
