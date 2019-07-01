vector<i64> tree(n << 1, -INF);
auto put = [&] (int pos, i64 val) {
  for (tree[pos += n] = val; pos > 1; pos /= 2) {
    tree[pos >> 1] = max(tree[pos], tree[pos ^ 1]);
  }
};
// [L, R)
auto ask = [&] (int L, int R) {
  i64 res = -INF;
  for (L += n, R += n; L < R; L /= 2, R /= 2) {
    if (L & 1) uax(res, tree[L++]);
    if (R & 1) uax(res, tree[--R]);
  }
  return res;
};
