/*
First, construct a dfs order of the given tree,with in time and out time
for each node.
Make a merge-sort tree (segment tree with sorted vectors at each node) from
this dfs-order. Each node is a sorted vector of pair(depth, cost).
binary search for the highest depth at each node in range,
then return minimum inside the range [start, d].
*/
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
inline std::ostream &operator << (std::ostream & os,const std::multiset<T,greater<T>>& v) {
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
#define len(v) ((int) (v).size())
struct SegTree {
    int n;
    vector<vector<pair<int,int>>> t;
    vector<pair<int,int>> a;
    vector<vector<int>> mnn;
    SegTree(int n, vector<pair<int,int>> &vec): n(n), a(vec) {
        t.resize(n << 2);
        mnn.resize(n << 2);
        build(1, 1, n);
    }
    void build(int i, int l, int r) {
        if (l == r) {
            t[i] = {a[l]};
            mnn[i] = {a[l].second};
            return;
        }
        int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m + 1, r);
        t[i].resize(len(t[i << 1]) + len(t[i << 1 | 1]));
        merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        mnn[i].resize(r - l + 1);
        mnn[i][0] = t[i][0].second;
        for (int j = 1; j < r - l + 1; ++j)
            mnn[i][j] = min(mnn[i][j - 1], t[i][j].second);
    }
    int _ask(int i, int l, int r, int L, int R, int d) {
        if (L > r || R < l) return MOD;
        if (L <= l && R >= r) {
            int k = (int) (upper_bound(all(t[i]), make_pair(d, MOD)) - t[i].begin());
            if (k) return mnn[i][k - 1];
            else return MOD;
        }
        int m = (l + r) >> 1;
        return min(_ask(i << 1, l, m, L, R, d),
                _ask(i << 1 | 1, m + 1, r, L, R, d));
    }
    int ask(int L, int R, int d) {
        return _ask(1, 1, n, L, R, d);
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r;
    cin >> n >> r;
    --r;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> tin(n), tout(n), dep(n);
    int timer = 0;
    vector<pair<int,int>> order(n + 1);
    function<void(int,int)> dfs = [&] (int u, int pa) {
        tin[u] = ++timer;
        dep[u] = (pa == -1 ? 0 : dep[pa] + 1);
        order[timer] = {dep[u], a[u]};
        for (int v: tree[u]) {
            if (v != pa) dfs(v, u);
        }
        tout[u] = timer;
    };
    dep[r] = 0;
    dfs(r, -1);
    SegTree seg(n, order);
    int q;
    cin >> q;
    int ans = 0;
    while (q--) {
        int x, k;
        cin >> x >> k;
        x = (x + ans) % n;
        k = (k + ans) % n;
        ans = seg.ask(tin[x], tout[x], k + dep[x]);
        cout << ans << '\n';
    }

    return 0;
}
