template<typename T>
struct sparse_table {
  function<T(T,T)> F;
  vector<vector<T>> table;
  vector<int> logn;
  int n, k;
  sparse_table(vector<T> &vec, function<T(T,T)> func): F(func) {
    n = (int) vec.size();
    logn.resize(n + 1);
    logn[1] = 0;
    for (int i = 2; i <= n; ++i)
      logn[i] = 1 + logn[i >> 1];
    k = logn[n];
    table.assign(k + 1, vector<T>(n));
    table[0] = vec;
    for (int i = 1; i <= k; ++i) {
      for (int j = 0; j + (1 << i) <= n; ++j) {
        table[i][j] = F(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T ask(int L, int R) {
    int j = logn[R - L + 1];
    return F(table[j][L], table[j][R - (1 << j) + 1]);
  }
};
