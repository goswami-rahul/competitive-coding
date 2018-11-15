#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
#define ll long long int
#define el "\n"
#define sqr(x) ((x) * (x))
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
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ": " << p.second << ")";
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
vector<vector<int>> tree;
vector<vector<int>> par;
vector<int> depth, see;
int tim = 0;
const int LOGN = 18;
inline int dfs(int u = 0, int pa = 0, int d = 0) {
    depth[u] = d;
    par[u][0] = pa;
    see[u] = tim++;
    for (int i = 1; i < LOGN; ++i) {
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for (int v: tree[u]) {
        dfs(v, u, d + 1);
    }
}
inline int lca(int u, int v) {
    if (u == v) return u;
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[par[u][i]] >= depth[v]) {
            u = par[u][i];
        }
    }
    assert(depth[u] == depth[v]);
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; --i) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

struct SegTreeLCA {
    vector<int> tree;
    int n;
    SegTreeLCA(size_t sz) {
        n = (int) sz;
        tree.resize(4 * n);
        build(1, n, 1);
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = tl - 1;
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = lca(tree[idx << 1], tree[idx << 1 | 1]);
    }
    int ask_util(int idx, int tl, int tr, int L, int R) {
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
            return lca(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    int ask(int L, int R) {
        return ask_util(1, 1, n, L, R);
    }
};
struct SegTreeMin {
    vector<pair<int,int>> tree;
    int n;
    SegTreeMin(size_t sz) {
        n = (int) sz;
        tree.resize(4 * n);
        build(1, n, 1);
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = make_pair(see[tl - 1], tl - 1);
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = min(tree[idx << 1], tree[idx << 1 | 1]);
    }
    pair<int,int> ask_util(int idx, int tl, int tr, int L, int R) {
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
            return min(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    int ask(int L, int R) {
        return ask_util(1, 1, n, L, R).second;
    }
};
struct SegTreeMax {
    vector<pair<int,int>> tree;
    int n;
    SegTreeMax(size_t sz) {
        n = (int) sz;
        tree.resize(4 * n);
        build(1, n, 1);
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = make_pair(see[tl - 1], tl - 1);
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
    }
    pair<int,int> ask_util(int idx, int tl, int tr, int L, int R) {
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
            return max(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    int ask(int L, int R) {
        return ask_util(1, 1, n, L, R).second;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    tree.resize(n);
    depth.resize(n);
    see.resize(n);
    par.assign(n, vector<int>(LOGN));
    for (int i = 1; i < n; ++i) {
        int u;
        cin >> u;
        --u;
        tree[u].push_back(i);
    }
    tim = 0;
    dfs();
    SegTreeLCA seglca(n);
    SegTreeMin segmin(n);
    SegTreeMax segmax(n);
    while (q--) {
        int L, R;
        cin >> L >> R;
        int u = segmin.ask(L, R) + 1, v = segmax.ask(L, R) + 1;
        int x;
        if (u == L) {
            x = seglca.ask(u + 1, R);
        } else if (u == R) {
            x = seglca.ask(L, u - 1);
        } else {
            x = lca(seglca.ask(L, u - 1), seglca.ask(u + 1, R));
        }
        int y;
        if (v == L) {
            y = seglca.ask(v + 1, R);
        } else if (v == R) {
            y = seglca.ask(L, v - 1);
        } else {
            y = lca(seglca.ask(L, v - 1), seglca.ask(v + 1, R));
        }
        int dep, ans;
        if (depth[x] > depth[y]) {
            dep = depth[x];
            ans = u;
        } else {
            dep = depth[y];
            ans = v;
        }
        cout << ans << ' ' << dep << '\n';
    }

    return 0;
}
