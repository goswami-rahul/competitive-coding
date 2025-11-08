vector<int> bit(n); 
// i ∈ [0, n)
auto add = [&] (int i, int val) {
  for (++i; i <= n; i += i & -i)
    bit[i - 1] += val;
};
auto get = [&] (int i) { 
  // sum of [0, i]
  int res = 0;
  for (++i; i > 0; i -= i & -i)
    res += bit[i - 1];
  return res;
};

/*******************/

template <class T>
struct Fenwick {
  int n;
  vector<T> bit;
  Fenwick(int _n): n(_n), bit(n + 1, 0) {};
  Fenwick(int _n, int inival): n(_n), bit(n + 1, 0) {
    for (int i = 1; i <= n; ++i)
      add(i, inival);
  }
  T ask(int pos) {  // sum of [1, pos]
    T ans = 0;
    for(++pos; pos > 0; pos -= pos & -pos)
      ans += bit[pos];
    return ans;
  }
  T ask(int L, int R) { // [L, R]
    return ask(R) - ask(L - 1);
  }
  T at(int pos) {
    return ask(pos, pos);
  }
  void add(int pos, T v) {  // pos in [0, n)
    if (++pos < 0) return;
    for (; pos <= n; pos += pos & -pos)
        bit[pos] += v;
  }
};
