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
/*************************************************************/

#define Op max
int a[N][M];
int f[LM][N][M];
int g[LM][LN][M][N];
void build() {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= m; i++) {
      f[0][k][i] = a[k - 1][i - 1];
    }
    for (int j = 1; 1 << j <= m; j++) {
      for (int i = 0; i + (1 << j) - 1 <= m; i++) {
        f[j][k][i] = Op(f[j - 1][k][i], f[j - 1][k][i + (1 << (j - 1))]);
      }
    }
  }
  for (int k = 1; k <= m; k++) {
    for (int l = 0; k + (1 << l) - 1 <= m; l++) {
      for (int i = 1; i <= n; i++) {
        g[l][0][k][i] = f[l][i][k];
      }
      for (int j = 1; 1 << j <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 <= n; i++) {
          g[l][j][k][i] = Op(g[l][j - 1][k][i], g[l][j - 1][k][i + (1 << (j - 1))]);
        }
      }
    }
  }
}
int ask(int x1, int y1, int x2, int y2) {
  ++x1, ++y1, ++x2, ++y2;
  int u = x2 - x1 + 1, v = y2 - y1 + 1;
  int lgu = logn[u];
  int lgv = logn[v];
  int res = g[lgv][lgu][y1][x1];
  res = Op(res, g[lgv][lgu][y1 + v - (1 << (lgv))][x1 + u - (1 << (lgu))]);
  res = Op(res, g[lgv][lgu][y1][x1 + u - (1 << (lgu))]);
  res = Op(res, g[lgv][lgu][y1 + v - (1 << (lgv))][x1]);
  return res;
}
#undef Op
