/*
 * Construct a segment tree where each node(L, R) represent a vector from
 * L to R. We can merge the two nodes by simple vector additions.
 * For the update, we maintain the current values of angles between adjacent nodes.
 * And calculate the relative angle rotation anti-clockwise.
 * Now, the update becomes simply rotating all vectors from s to the end
 * by that angle. We update lazily.
 */
#include<cmath>
#include<cstdio>
#include<iostream>
#include<vector>
#include<ios>
#define PI 3.14159265358979323846
using namespace std;

struct Node {
    long double x, y;
    int lz;
    Node() {
        x = 0;
        y = 0;
        lz = 0;
    };
};
Node combine(const Node left, const Node right) {
    Node u;
    u.x = left.x + right.x;
    u.y = left.y + right.y;
    return u;
}
struct SegTree {
    vector<Node> tree;
    vector<int> arr;
    int n;
    SegTree(size_t sz, vector<int> &vec) {
        arr = vec;
        n = (int) sz;
        tree.resize(4 * n);
        build(1, n, 1);
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx].y = arr[tl - 1];
            tree[idx].x = 0;
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    void push(int idx, bool has_child) {
        if (tree[idx].lz == 0) return;
        rotate(tree[idx], tree[idx].lz);
        if (has_child) {
            tree[idx << 1].lz += tree[idx].lz;
            tree[idx << 1 | 1].lz += tree[idx].lz;
        }
        tree[idx].lz = 0;
    }
    void rotate(Node &k, int deg) {
        long double r = (long double) deg * PI / 180, x = k.x, y = k.y;
        k.x = x * cos(r) - y * sin(r);
        k.y = x * sin(r) + y * cos(r);
    }
    void update_util(int idx, int tl, int tr, int L, int R, int deg) {
        if (tl == L && tr == R) {
            tree[idx].lz += deg;
            return;
        }
        push(idx, tr > tl);
        int m = (tl + tr) >> 1;
        if (R > m) {
            update_util(idx << 1 | 1, m + 1, tr, max(L, m + 1), R, deg);
        }
        if (L < m + 1) {
            update_util(idx << 1, tl, m, L, min(R, m), deg);
        }
        push(idx << 1, tl < m);
        push(idx << 1 | 1, m + 1 < tr);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    void update(int x, int y, int deg) {
        update_util(1, 1, n, x, y, deg);
    }
    void ans() {
        push(1, 1 < n);
        printf("%.2lf %.2lf\n", tree[1].x, tree[1].y);
    }
};
int main()
{
    int n, c;
    bool first = true;
    while (scanf("%d%d", &n, &c) != EOF) {
        if (first) first = false;
        else printf("\n");
        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);
        SegTree seg(n, arr);
        vector<int> ang(n, 180);
        while (c--) {
            int s, a;
            scanf("%d%d", &s, &a);
            int deg = (3600 + a - ang[s]) % 360;
            seg.update(s + 1, n, deg);
            seg.ans();
            ang[s] = a;
        }
    }
    return 0;
}
