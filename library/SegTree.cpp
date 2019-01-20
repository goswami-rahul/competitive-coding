struct SegTree {
    struct data {
        ll sum, pre, suf, ans;
        data() {};
        data(ll _1, ll _2, ll _3, ll _4): sum(_1), pre(_2), suf(_3), ans(_4) {};
    };
    vector<data> tree;
    vector<ll> arr;
    int n;
    SegTree(size_t sz, vector<ll> &vec) {
        // 1-indexed vec!
        arr = vec;
        n = (int) sz;
        assert(sz == vec.size() - 1);
        tree.resize(4 * n);
        build(1, n, 1);
    }
    data make_data(int pos) {
        ll x = arr[pos];
        return data(x, x, x, x);
    }
    data combine(const &data left, const &data right) {
        data node;
        node.sum = left.sum + right.sum;
        node.pre = max(left.pre, left.sum + right.pre);
        node.suf = max(right.suf, right.sum + left.suf);
        node.ans = left.suf + right.pre;
        node.ans = max(node.ans, left.ans);
        node.ans = max(node.ans, right.ans);

        return node;
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = make_data(tl);
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    data ask_util(int idx, int tl, int tr, int L, int R) {
        assert(L <= R);
        if (L == tl && R == tr) {
            return tree[idx];
        }
        int m = (tr + tl) >> 1;
        if (L > m) {
            return ask_util(idx << 1 | 1, m + 1, tr, L, R);
        } else if (R < m + 1) {
            return ask_util(idx << 1, tl, m, L, R);
        } else {
            return combine(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    void update_util(int tl, int tr, int idx, int pos) {
        if (tl == tr) {
            tree[idx] = make_data(pos);
            return;
        }
        int m = (tl + tr) >> 1;
        if (pos <= m) update_util(tl, m, idx << 1, pos);
        else update_util(m + 1, tr, idx << 1 | 1, pos);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    void update(int pos, ll newval) {
        arr[pos] = newval;
        update_util(1, n, 1, pos);
    }
    ll ask() {
        return ask_util(1, 1, n, 1, n).ans;
    }
};

struct SegTreeMax {
    vector<ll> tree;
    int n;
    SegTree(size_t sz, vector<ll> &vec) {
        // 1-indexed vec!
        arr = vec;
        n = (int) sz;
        assert(sz == vec.size() - 1);
        tree.resize(4 * n);
        build(1, n, 1, vec);
    }
    void build(int tl, int tr, int idx, vector<ll> &vec) {
        if (tl == tr) {
            tree[idx] = vec[tl];
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1, vec);
        build(m + 1, tr, idx << 1 | 1, vec);
        tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
    }
    data ask_util(int idx, int tl, int tr, int L, int R) {
        if (L == tl && R == tr) {
            return tree[idx];
        }
        int m = (tr + tl) >> 1;
        if (L > m) {
            return ask_util(idx << 1 | 1, m + 1, tr, L, R);
        } else if (R < m + 1) {
            return ask_util(idx << 1, tl, m, L, R);
        } else {
            return max(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    ll ask(int L, int R) {
        return ask_util(1, 1, n, L, R);
    }
};
