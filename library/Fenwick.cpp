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
    vector<T> values(int upto = -1) {
        if (upto == -1) return values(n);
        vector<T> fenwick_values;
        for (int i = 1; i <= upto; ++i)
            fenwick_values.push_back(ask(i, i));
        return fenwick_values;
    }
};
