int A[MAXN];
int BIT[MAXN];

void add(int idx, int val) {
    for (; idx < MAXN; idx += idx&-idx)
        BIT[idx] += val;
}

int get(int idx) {
    int ret = 0;
    for (; idx > 0; idx -= idx&-idx)
        ret += BIT[idx];
    return ret;
}
// greatest idx with cumulative sum = k
auto findkth = [&] (int k) {
    int mask = 1 << LOGN, idx = 0;
    while (mask) {
        int cur = idx + mask;
        mask >>= 1;
        if (cur > n)
            continue;
        if (k >= BIT[cur]) {
            idx = cur;
            k -= BIT[cur];
        }
    }
    if (k == 0) return idx;
    return -2;
};
/****************/
struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
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
  T ask(int R) {
    T ans = 0;
    for(int x = R; x > 0; x -= x & -x)
      ans += bit[x];
    return ans;
  }
  T ask(int L, int R) {
    return ask(R) - ask(L - 1);
  }
  T at(int pos) {
    return ask(pos, pos);
  }
  void add(int pos, T v) {
    if(pos <= 0) return;
    for(; pos <= n; pos += pos & -pos)
        bit[pos] += v;
  }
  // greatest idx with cumulative sum = k
  int kth(int k) {
    int idx = 0;
    for (int mask = 1 << LOGN; mask; mask >>= 1) {
      int cur = idx + mask;
      if (cur <= n && BIT[cur] <= k) {
        k -= BIT[cur];
        idx = cur;
      }
    }
    return (k == 0 ? idx : -1);
  };
  vector<T> values(int upto = -1) {
    if (upto == -1) return values(n);
    vector<T> fenwick_values;
    for (int i = 1; i <= upto; ++i)
        fenwick_values.push_back(ask(i, i));
    return fenwick_values;
  }
};
