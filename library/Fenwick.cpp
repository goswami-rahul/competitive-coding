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
template <class T>
struct Fenwick {
    int n;
    vector<T> bit;
	Fenwick(int n): n(n), bit(n + 1, 0) {}
	T qry(int x) {
		T ans = 0;
		for(; x > 0; x -= x & -x)
			ans += bit[x];
		return ans;
	}
	void upd(int x, T v) {
		if(x <= 0) return;
		for(; x <= n; x += x & -x)
            bit[x] += v;
    }
};
