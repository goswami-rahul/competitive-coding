#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
using ll = long long int;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
template <typename T> inline void ckmax(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void ckmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << endl;
	err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v) {
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++) {
        if(!first) os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v) {
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
    }
    return os << "}";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::unordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::multiset<T>& v) {
    return os << std::vector<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const ordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}

const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
struct SegTree {
    vector<i64> tree, lazy;
    int n;
    SegTree(int sz, vector<int> &vec) {
        n = sz;
        tree.resize(n << 2);
        lazy.resize(n << 2);
        build(1, 1, n, vec);
    }
    void build(int id, int tl, int tr, vector<int> &vec) {
        if (tl == tr) {
            tree[id] = 1LL << vec[tl];
            return;
        }
        int m = (tl + tr) >> 1;
        build(id << 1, tl, m, vec);
        build(id << 1 | 1, m + 1, tr, vec);
        tree[id] = tree[id << 1] | tree[id << 1 | 1];
    }
    void push(int id, int tl, int tr) {
        if (lazy[id]) {
            tree[id] = lazy[id];
            if (tl < tr) {
                lazy[id << 1] = lazy[id];
                lazy[id << 1 | 1] = lazy[id];
            }
        }
        lazy[id] = 0;
    }
    void _upd(int id, int tl, int tr, int L, int R, int mask) {
        push(id, tl, tr);
        if (tl == L && tr == R) {
            lazy[id] = 1LL << mask;
            return;
        }
        int m = (tl + tr) >> 1;
        if (L <= m) _upd(id << 1, tl, m, L, min(m, R), mask);
        if (R > m) _upd(id << 1 | 1, m + 1, tr, max(L, m + 1), R, mask);
        push(id << 1, tl, m);
        push(id << 1 | 1, m + 1, tr);
        tree[id] = tree[id << 1] | tree[id << 1 | 1];
    }
    void update(int L, int R, int c) {
        _upd(1, 1, n, L, R, c);
    }
    i64 _ask(int id, int tl, int tr, int L, int R) {
        push(id, tl, tr);
        if (tl == L && tr == R) {
            return tree[id];
        }
        int m = (tl + tr) >> 1;
        if (R <= m) {
            return _ask(id << 1, tl, m, L, R);
        }
        if (L > m) {
            return _ask(id << 1 | 1, m + 1, tr, L, R);
        }
        return _ask(id << 1, tl, m, L, min(R, m)) | _ask(id << 1 | 1, m + 1, tr, max(L, m + 1), R);
    }
    int ask(int L, int R) {
        return __builtin_popcountll(_ask(1, 1, n, L, R));
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &e: a) {
        cin >> e;
        --e;
    }
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    int timer = 0;
    vector<int> tin(n), tout(n);
    vector<int> order = {42};
    function<void(int,int)> dfs = [&] (int u, int pa) {
        tin[u] = ++timer;
        order.push_back(a[u]);
        for (int v: tree[u]) {
            if (v == pa) continue;
            dfs(v, u);
        }
        tout[u] = timer;
    };
    dfs(0, -1);
    SegTree seg(n, order);
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, c;
            cin >> v >> c;
            --v; --c;
            seg.update(tin[v], tout[v], c);
        } else {
            int v;
            cin >> v;
            --v;
            cout << seg.ask(tin[v], tout[v]) << '\n';
        }
    }

    return 0;
}
